# @file icub_models.py
# @authors Giulio Romualdi
# @copyright 2022 Istituto Italiano di Tecnologia Released under the terms of the Creative Commons Attribution Share Alike 4.0 International

from os import listdir
from os.path import dirname, join, isdir, exists, realpath
from typing import List


def get_models_path() -> str:
    relative_path = '@ICUB_MODELS_CXX_PYTHON_INSTALL_RELATIVE_DIR@'
    # If relative_path starts with @, it is a not escaped string
    # from CMake, i.e. that means that the file was installed via setup.py
    # let's substitute relative_path with its default value
    if relative_path.startswith('@'):
        relative_path = '../../../..'
    root = realpath(join(dirname(__file__), relative_path))
    return join(root, 'share', 'iCub', 'robots')

def get_robot_names() -> List[str]:
    return listdir(get_models_path())

def get_model_file(robot_name: str) -> str:
    model_file = join(get_models_path(), robot_name, 'model.urdf')

    if exists(model_file):
        return model_file
    else:
        return ''
