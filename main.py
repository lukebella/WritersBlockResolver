
import tensorflow.compat.v1 as tf
import numpy as np
import os
from magenta.common import tf_utils
from note_seq import audio_io
from magenta.models.onsets_frames_transcription import audio_label_data_utils
from magenta.models.onsets_frames_transcription import configs
from magenta.models.onsets_frames_transcription import constants
from magenta.models.onsets_frames_transcription import data
from magenta.models.onsets_frames_transcription import infer_util
from magenta.models.onsets_frames_transcription import train_util
import note_seq
from note_seq import midi_io
from note_seq import sequences_lib

tf.disable_v2_behavior()

## Define model and load checkpoint
## Only needs to be run once.
MAESTRO_CHECKPOINT_DIR = 'C:/Users/lenovo/Tesi/magenta/magenta/models/onsets_frames_transcription/maestro/train'

config = configs.CONFIG_MAP['onsets_frames']
hparams = config.hparams
hparams.use_cudnn = False
hparams.batch_size = 1
checkpoint_dir = MAESTRO_CHECKPOINT_DIR

examples = tf.placeholder(tf.string, [None])

dataset = data.provide_batch(
    examples=examples,
    preprocess_examples=True,
    params=hparams,
    is_training=False,
    shuffle_examples=False,
    skip_n_initial_records=0)

estimator = train_util.create_estimator(
    config.model_fn, checkpoint_dir, hparams)

iterator = tf.data.make_initializable_iterator(dataset)
next_record = iterator.get_next()

#-----------------------------------------------------------------------------

name_of_file = "provafileeeee.wav"
#value = f.read()

def make_dict(name_of_file):
    with open(name_of_file,'r+b') as f:
        return {f.name:f.read()}

uploaded = make_dict(name_of_file)
#print(uploaded)
to_process = []
for fn in uploaded.keys():
    print('User uploaded file "{name}" with length {length} bytes'.format(name=fn, length=len(uploaded[fn])))
    wav_data = uploaded[fn]
    example_list = list(
        audio_label_data_utils.process_record(
            wav_data=wav_data,
            sample_rate=hparams.sample_rate,
            ns=note_seq.NoteSequence(),
            example_id=fn,
            min_length=0,
            max_length=-1,
            allow_empty_notesequence=True))
    assert len(example_list) == 1
    to_process.append(example_list[0].SerializeToString())

    print('Processing complete for', fn)

sess = tf.Session()

sess.run([
    tf.initializers.global_variables(),
    tf.initializers.local_variables()
])

sess.run(iterator.initializer, {examples: to_process})


def transcription_data(params):
    del params
    return tf.data.Dataset.from_tensors(sess.run(next_record))

input_fn = infer_util.labels_to_features_wrapper(transcription_data)

#===================================================================================================

prediction_list = list(estimator.predict(input_fn,yield_single_examples=False))
assert len(prediction_list) == 1

sequence_prediction = note_seq.NoteSequence.FromString( prediction_list[0]['sequence_predictions'][0])

# Ignore warnings caused by pyfluidsynth
import warnings
warnings.filterwarnings("ignore", category=DeprecationWarning)

note_seq.plot_sequence(sequence_prediction)
#note_seq.play_sequence(sequence_prediction, note_seq.midi_synth.fluidsynth,colab_ephemeral=False)

#============================================================================================================================

import gym_patch
with gym_patch.patch_register_gym_env():
  from tensor2tensor import models
from tensor2tensor import problems
from tensor2tensor.data_generators import text_encoder
from tensor2tensor.utils import decoding
from tensor2tensor.utils import trainer_lib

from magenta.models.score2perf import score2perf
import note_seq

tf.disable_v2_behavior()
SF2_PATH = 'Yamaha-C5-Salamander-JNv5.1.sf2'
SAMPLE_RATE = 16000
midi_file='C:/Users/lenovo/Tesi/magenta/magenta/models/Transformer\moonlight_sonata.mid'
# Upload a MIDI file and convert to NoteSequence.
def upload_midi():
  data = list(midi_file.values())
  if len(data) > 1:
    print('Multiple files uploaded; using only one.')
  return note_seq.midi_to_note_sequence(data[0])

# Decode a list of IDs.
def decode(ids, encoder):
  ids = list(ids)
  if text_encoder.EOS_ID in ids:
    ids = ids[:ids.index(text_encoder.EOS_ID)]
  return encoder.decode(ids)

#==========================================================================

model_name = 'transformer'
hparams_set = 'transformer_tpu'
ckpt_path = 'C:/Users/lenovo/Tesi/magenta/magenta/models/Transformer/unconditional_model_16.ckpt'

class PianoPerformanceLanguageModelProblem(score2perf.Score2PerfProblem):
  @property
  def add_eos_symbol(self):
    return True

problem = PianoPerformanceLanguageModelProblem()
unconditional_encoders = problem.get_feature_encoders()

# Set up HParams.
hparams = trainer_lib.create_hparams(hparams_set=hparams_set)
trainer_lib.add_problem_hparams(hparams, problem)
hparams.num_hidden_layers = 16
hparams.sampling_method = 'random'

# Set up decoding HParams.
decode_hparams = decoding.decode_hparams()
decode_hparams.alpha = 0.0
decode_hparams.beam_size = 1

# Create Estimator.
run_config = trainer_lib.create_run_config(hparams)
estimator = trainer_lib.create_estimator(
    model_name, hparams, run_config,
    decode_hparams=decode_hparams)

# Create input generator (so we can adjust priming and
# decode length on the fly).
def input_generator():
  global targets
  global decode_length
  while True:
    yield {
        'targets': np.array([targets], dtype=np.int32),
        'decode_length': np.array(decode_length, dtype=np.int32)
    }

# These values will be changed by subsequent cells.
targets = []
decode_length = 0

# Start the Estimator, loading from the specified checkpoint.
input_fn = decoding.make_input_fn_from_generator(input_generator())
unconditional_samples = estimator.predict(
    input_fn, checkpoint_path=ckpt_path)

# "Burn" one.
_ = next(unconditional_samples)

#============================================================================
"""targets = unconditional_encoders['targets'].encode_note_sequence(
    primer_ns)

# Remove the end token from the encoded primer.
targets = targets[:-1]

decode_length = max(0, 4096 - len(targets))
if len(targets) >= 4096:
  print('Primer has more events than maximum sequence length; nothing will be generated.')

# Generate sample events.
sample_ids = next(unconditional_samples)['outputs']

# Decode to NoteSequence.
midi_filename = decode(
    sample_ids,
    encoder=unconditional_encoders['targets'])
ns = note_seq.midi_file_to_note_sequence(midi_filename)

# Append continuation to primer.
continuation_ns = note_seq.concatenate_sequences([primer_ns, ns])

# Play and plot.
note_seq.play_sequence(
    continuation_ns,
    synth=note_seq.fluidsynth, sample_rate=SAMPLE_RATE, sf2_path=SF2_PATH)
note_seq.plot_sequence(continuation_ns)"""