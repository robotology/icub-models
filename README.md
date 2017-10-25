# icub-models

Repository containing models automatically generated from the CAD file by [icub-model-generator](https://github.com/robotology-playground/icub-model-generator).

## Usage

The model in the repo can be used either directly from the repo, or by installing them.

While the files can be used directly by pointing your software to their location, they are
tipically used by software that uses either YARP, ROS or Gazebo. For this reason, the models
are installed as part of the `iCub` ROS package ([instructions](https://github.com/gerkey/ros1_external_use#installing-for-use-by-tools-like-roslaunch)) and following the [YARP guidelines on installing configuration files](http://www.yarp.it/yarp_data_dirs.html).

To make sure that this models are found by the software even when they are not installed in
system directories, tipically the [`YARP_DATA_DIRS`](http://www.yarp.it/yarp_data_dirs.html), 
[`ROS_PACKAGE_PATH`](http://wiki.ros.org/ROS/EnvironmentVariables#ROS_PACKAGE_PATH), and the [`GAZEBO_MODEL_PATH`](http://gazebosim.org/tutorials?tut=components#EnvironmentVariables) enviromental variables are modified appropriatly.


### From the source repo

In the case models are used from the repo, the first step is configure it with the following commands:

```sh
mkdir build
cd build
cmake ..
```

If `<icub-models>` is the location of the repo, some folders need to be appended to the mentioned env variables. On *nix system, this can be achived by adding to the `.bashrc` or equivalent file the following three lines:

```sh
export YARP_DATA_DIRS=${YARP_DATA_DIRS}:<icub-models>/build/iCub
export ROS_PACKAGE_PATH=${ROS_PACKAGE_PATH}:<icub-models>/build
export GAZEBO_MODEL_PATH=${GAZEBO_MODEL_PATH}:<icub-models>/build/iCub:<icub-models>/build/iCub/robots:<icub-models>/build
```

### By installing the models

To install the models instead, execute:

```sh
mkdir build
cd build
cmake -DCMAKE_INSTALL_PREFIX=<prefix> ..
cmake --build . --target install
```

Once the models are installed into a given prefix, edit the env variables as follows:

```sh
export YARP_DATA_DIRS=${YARP_DATA_DIRS}:<prefix>/share/iCub
export ROS_PACKAGE_PATH=${ROS_PACKAGE_PATH}:<prefix>/share
export GAZEBO_MODEL_PATH=${GAZEBO_MODEL_PATH}:<prefix>/share/iCub:<prefix>/share/iCub/robots:<prefix>/share
```
