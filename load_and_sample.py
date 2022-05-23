import numpy as np
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

class PianoPerformanceLanguageModelProblem(score2perf.Score2PerfProblem):
  @property
  def add_eos_symbol(self):
    return True


#path for model: ckpt_path = './Transformer/unconditional_model_16.ckpt'

class Model:

    targets = []
    decode_length = 0

    def __init__(self, ckpt_path):
        self.ckpt_path = ckpt_path
        self.model_name = 'transformer'
        self.hparams_set = 'transformer_tpu'

        self.problem = PianoPerformanceLanguageModelProblem()
        self.unconditional_encoders = self.problem.get_feature_encoders()

        self.hparams = trainer_lib.create_hparams(hparams_set=self.hparams_set)

    def load(self,ckpt_path):

        self.__init__(ckpt_path)

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
        unconditional_samples = estimator.predict(input_fn, checkpoint_path=self.ckpt_path)

        # "Burn" one.
        _ = next(unconditional_samples)

        return unconditional_samples


    def input_generator(self):
        while True:
            yield {
                'targets': np.array([Model.targets], dtype=np.int32),   #problem(?)
                'decode_length': np.array(Model.decode_length, dtype=np.int32)
            }

    def decode(self, ids, encoder):
        ids = list(ids)
        if text_encoder.EOS_ID in ids:
            ids = ids[:ids.index(text_encoder.EOS_ID)]
        return encoder.decode(ids)


    def sample(self):
        self.targets = []
        self.decode_length = 1024
        sample_ids = next(self.load(self.ckpt_path))['outputs']
        #print(sample_ids)
        print("Sequence generated")

        # Decode to NoteSequence.
        midi_filename = self.decode(sample_ids, encoder=self.unconditional_encoders['targets'])
        return midi_filename


if __name__ == '__main__':
    model = Model("./Transformer/unconditional_model_16.ckpt")
    midi_path = model.sample()
    print("MIDI Path: ", midi_path)



