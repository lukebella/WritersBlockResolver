"""Module that provides a patch for the function :func:`register_gym_env`"""

import contextlib
import functools
import importlib


@contextlib.contextmanager
def patch_register_gym_env():
  """Apply patch to the function
  :func:`tensor2tensor.rl.gym_utils.register_gym_env` within the context"""
  gym_utils = importlib.import_module("tensor2tensor.rl.gym_utils")
  old_register_gym_env = gym_utils.register_gym_env

  @functools.wraps(old_register_gym_env)
  def register_gym_env(class_entry_point, version="v0", kwargs=None):
    """Patched wrapper"""
    return old_register_gym_env(class_entry_point,
                                version=version,
                                kwargs={} if kwargs is None else kwargs)

  gym_utils.register_gym_env = register_gym_env
  yield register_gym_env
  gym_utils.register_gym_env = old_register_gym_env
