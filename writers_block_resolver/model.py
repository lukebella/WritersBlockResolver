import numpy as np
import tensorflow.compat.v1 as tf
import writers_block_resolver.gym_patch as gym_patch
import os
import shutil
with gym_patch.patch_register_gym_env():
    from tensor2tensor import models
from tensor2tensor import problems
from tensor2tensor.data_generators import text_encoder
from tensor2tensor.utils import decoding
from tensor2tensor.utils import trainer_lib
from magenta.models.score2perf import score2perf
import note_seq

tf.disable_v2_behavior()

class PianoPerformanceLanguageModelProblem(score2perf.Score2PerfProblem):
  @property
  def add_eos_symbol(self):
    return True


class Model:

    def __init__(self):
        self.targets = []
        self.decode_length = 0
        self.model_name = 'transformer'
        self.hparams_set = 'transformer_tpu'

        self.problem = PianoPerformanceLanguageModelProblem()
        self.unconditional_encoders = self.problem.get_feature_encoders()

        self.hparams = trainer_lib.create_hparams(hparams_set=self.hparams_set)
        self.unconditional_samples = None
        self.primer_ns = None

    def load(self,ckpt_path):

        #define and set hparams
        trainer_lib.add_problem_hparams(self.hparams, self.problem)
        self.hparams.num_hidden_layers = 16
        self.hparams.sampling_method = 'random'


        decode_hparams = decoding.decode_hparams()
        decode_hparams.alpha = 0.0
        decode_hparams.beam_size = 1

        # Create Estimator.
        run_config = trainer_lib.create_run_config(self.hparams)
        estimator = trainer_lib.create_estimator(
            self.model_name, self.hparams, run_config,
            decode_hparams=decode_hparams)


        # Start the Estimator, loading from the specified checkpoint.
        input_fn = decoding.make_input_fn_from_generator(self.input_generator())
        unconditional_samples = estimator.predict(input_fn, checkpoint_path=ckpt_path)

        # "Burn" one.
        _ = next(unconditional_samples)

        self.unconditional_samples = unconditional_samples
        return self


    def input_generator(self):
        while True:
            yield {
                'targets': np.array([self.targets], dtype=np.int32),   #problem(?)
                'decode_length': np.array(self.decode_length, dtype=np.int32)
            }

    def decode(self, ids, encoder):
        ids = list(ids)
        if text_encoder.EOS_ID in ids:
            ids = ids[:ids.index(text_encoder.EOS_ID)]
        return encoder.decode(ids)


    def sample(self):
        self.decode_length = 1024
        sample_ids = next(self.unconditional_samples)['outputs']
        #print(sample_ids) usare log cherrypy
        print("Sequence generated")

        # Decode to NoteSequence.
        midi_filename = self.decode(sample_ids, encoder=self.unconditional_encoders['targets'])
        return midi_filename

    def store(self, myFile):
        with open(myFile, 'r+b') as f:
            return f.read()

    def primingSequence(self, midiFile):
        """filenames = {
            'C major arpeggio': '/content/c_major_arpeggio.mid',
            'C major scale': '/content/c_major_scale.mid',
            'Clair de Lune': '/content/clair_de_lune.mid',
        }"""
        print(os.path.join(midiFile, ""))
        print(os.path.exists(midiFile))
        #'C:/Users/lenovo/Documents/JUCE_Projects/WritersBlockResolver/tt-942969/Transformer/c_major_scale.mid'  # @param ['C major arpeggio', 'C major scale', 'Clair de Lune', 'Upload your own!']
        self.primer_ns = note_seq.midi_file_to_note_sequence(midiFile)    #filenames[primer]

        # Handle sustain pedal in the primer.
        self.primer_ns = note_seq.apply_sustain_control_changes(self.primer_ns)

        # Trim to desired number of seconds.
        max_primer_seconds = 20  # @param {type:"slider", min:1, max:120}
        if self.primer_ns.total_time > max_primer_seconds:
            print('Primer is longer than %d seconds, truncating.' % max_primer_seconds)
            primer_ns = note_seq.extract_subsequence(
                self.primer_ns, 0, max_primer_seconds)

        # Remove drums from primer if present.
        if any(note.is_drum for note in self.primer_ns.notes):
            print('Primer contains drums; they will be removed.')
            notes = [note for note in self.primer_ns.notes if not note.is_drum]
            del self.primer_ns.notes[:]
            self.primer_ns.notes.extend(notes)

        # Set primer instrument and program.
        """for note in primer_ns.notes:
            note.instrument = 1
            note.program = 0

        # Play and plot the primer.
        note_seq.play_sequence(
            primer_ns,
            synth=note_seq.fluidsynth, sample_rate=SAMPLE_RATE, sf2_path=SF2_PATH)
        note_seq.plot_sequence(primer_ns)"""

        return self

    def continuation(self):
        self.targets = self.unconditional_encoders['targets'].encode_note_sequence(
            self.primer_ns)

        # Remove the end token from the encoded primer.
        self.targets = self.targets[:-1]

        decode_length = max(0, 4096 - len(self.targets))
        if len(self.targets) >= 4096:
            print('Primer has more events than maximum sequence length; nothing will be generated.')

        # Generate sample events.
        sample_ids = next(self.unconditional_samples)['outputs']

        print(sample_ids)
        # Decode to NoteSequence.
        midi_filename = self.decode(
            sample_ids,
            encoder=self.unconditional_encoders['targets'])
        ns = note_seq.midi_file_to_note_sequence(midi_filename)

        # Append continuation to primer.
        continuation_ns = note_seq.concatenate_sequences([self.primer_ns, ns])

        # note_seq.sequence_proto_to_midi_file(continuation_ns, '/tmp/continuation.mid')
        """
        continuation_ns = note_seq.concatenate_sequences([self.primer_ns, ns])
        print(continuation_ns)"""
        print("Continuation generated")
        return continuation_ns   #I don't think it's MIDI, do note_seq.sequence_proto_to_midi_file instead? Or decoding after concatenating?



"""def copy_dir(midi_filename):
    dest = os.path.join(os.getcwd(), "MIDI_file.mid")
    shutil.copy(midi_filename, dest)

if __name__ == '__main__':
    model = Model().load('C:/Users/lenovo/Tesi/prova/Transformer/unconditional_model_16.ckpt')

    #midi_path = model.sample()
    continuation_ns = model.continuation()


    #copy_dir(midi_path)"""