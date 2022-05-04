print('Importing libraries...')

import numpy as np
import os
import tensorflow.compat.v1 as tf

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

print('Done!')


#=======================================================

SF2_PATH = 'file://C:/Users/lenovo/Tesi/magenta/magenta/models/Transformer/Yamaha-C5-Salamander-JNv5.1.sf2'
SAMPLE_RATE = 16000
midi_file='file://C:/Users/lenovo/Tesi/magenta/magenta/models/Transformer/moonlight_sonata.mid'
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
ckpt_path = 'file://C:/Users/lenovo/Tesi/magenta/magenta/models/Transformer/unconditional_model_16.ckpt'

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
unconditional_samples = estimator.predict(input_fn, checkpoint_path=ckpt_path)

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