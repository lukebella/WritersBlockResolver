
import tensorflow.compat.v1 as tf
import librosa
import numpy as np
import os
print(os.getcwd())
import wave

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

uploaded_tuple = librosa.load('C:/Users/lenovo/Tesi/prova/11 A BIT OF SHAME.wav',48000)
uploaded = bytearray(str(uploaded_tuple), 'utf-8')

to_process = []
#frame = uploaded.readframes()
print('User uploaded file "{name}" with length {length} bytes'.format(
    name=uploaded, length=len(uploaded)))
wav_data = uploaded
example_list = audio_label_data_utils.process_record(
        wav_data=wav_data,
        sample_rate=hparams.sample_rate,
        ns=note_seq.NoteSequence(),
        example_id=uploaded,
        min_length=0,
        max_length=-1,
        allow_empty_notesequence=True)
#assert len(example_list) == 1
#to_process.append(example_list[0].SerializeToString())

print('Processing complete for', uploaded)

sess = tf.Session()

#dt = np.dtype(example_list)    #added
#print("kind= ",dt.kind)        #added

#examples = tf.compat.v1.placeholder(np.dtype(example_list))    #added

sess.run([
    tf.initializers.global_variables(),
    tf.initializers.local_variables()
])

sess.run(iterator.initializer, {examples: example_list})


def transcription_data(params):
    del params
    return tf.data.Dataset.from_tensors(sess.run(next_record))


input_fn = infer_util.labels_to_features_wrapper(transcription_data)