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


class PianoPerformanceLanguageModelProblem(score2perf.Score2PerfProblem):
  @property
  def add_eos_symbol(self):
    return True



class Model():

    targets = []
    decode_length = 0

    def load(self, ckpt_path):

        #path for model: ckpt_path = './Transformer/unconditional_model_16.ckpt'
        model_name = 'transformer'
        hparams_set = 'transformer_tpu'

        problem = PianoPerformanceLanguageModelProblem()
        unconditional_encoders = problem.get_feature_encoders()

        #define and set hparams
        hparams = trainer_lib.create_hparams(hparams_set=hparams_set)
        trainer_lib.add_problem_hparams(hparams, problem)
        hparams.num_hidden_layers = 16
        hparams.sampling_method = 'random'


        decode_hparams = decoding.decode_hparams()
        decode_hparams.alpha = 0.0
        decode_hparams.beam_size = 1

        # Create Estimator.
        run_config = trainer_lib.create_run_config(hparams)
        estimator = trainer_lib.create_estimator(
            model_name, hparams, run_config,
            decode_hparams=decode_hparams)


        # Start the Estimator, loading from the specified checkpoint.
        input_fn = decoding.make_input_fn_from_generator(self.input_generator(self.targets,self.decode_length))
        unconditional_samples = estimator.predict(input_fn, checkpoint_path=ckpt_path)

        # "Burn" one.
        _ = next(unconditional_samples)




    def input_generator(targets,decode_length):
        while True:
            yield {
                'targets': np.array([targets], dtype=np.int32),
                'decode_length': np.array(decode_length, dtype=np.int32)
            }




    def sample(self):
        return