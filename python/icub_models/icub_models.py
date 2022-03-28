# @file icub_models.py
# @authors Giulio Romualdi
# @copyright 2022 Istituto Italiano di Tecnologia Released under the terms of the Creative Commons Attribution Share Alike 4.0 International

from os import listdir
from os.path import dirname, join, isdir, exists
from typing import List


def get_models_path() -> str:
    root = dirname(dirname(dirname(dirname(dirname(__file__)))))
    return join(root, 'share', 'icub_models', 'iCub', 'robots')

def get_robot_names() -> List[str]:
    return listdir(get_models_path())

def get_model_file(robot_name: str) -> str:
    model_file = join(get_models_path(), robot_name, 'model.urdf')

    if exists(model_file):
        return model_file
    else:
        return ''
