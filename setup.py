# Copyright (C) 2022 Istituto Italiano di Tecnologia (IIT). All rights reserved.
# This software may be modified and distributed under the terms of the
# Released under the terms of the BSD 3-Clause License

from setuptools import setup
from glob import glob
import os


if __name__ == '__main__':

    all_files = glob('./iCub/**/*.*', recursive=True)
    data_files = [(os.path.join('share', 'icub_models', os.path.split(path)[0]),
                   [os.path.join(os.path.split(path)[0], os.path.split(path)[1])])
                  for path in all_files]

    setup(data_files = data_files)
