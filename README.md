# icub-models

Repository containing models [automatically](https://github.com/robotology-playground/icub-model-generator/blob/master/.travis.yml#L76) generated from the CAD file by [icub-model-generator](https://github.com/robotology-playground/icub-model-generator).

The model contained in this repo are licensed under the [Creative Commons Attribution-ShareAlike 4.0 International License (CC BY-SA 4.0) ](https://creativecommons.org/licenses/by-sa/4.0/).

## Usage

The model in the repo can be used either directly from the repo, or by installing them.

While the files can be used directly by pointing your software to their location, they are
tipically used by software that uses either YARP, ROS or Gazebo. For this reason, the models
are installed as part of the `iCub` ROS package ([instructions](https://github.com/gerkey/ros1_external_use#installing-for-use-by-tools-like-roslaunch)) and following the [YARP guidelines on installing configuration files](http://www.yarp.it/yarp_data_dirs.html).

To make sure that this models are found by the software even when they are not installed in
system directories, tipically the [`YARP_DATA_DIRS`](http://www.yarp.it/yarp_data_dirs.html) for [YARP](https://github.com/robotology/yarp), 
[`ROS_PACKAGE_PATH`](http://wiki.ros.org/ROS/EnvironmentVariables#ROS_PACKAGE_PATH) for [ROS1](https://www.ros.org/), [`AMENT_PREFIX_PATH`](http://design.ros2.org/articles/ament.html) for [ROS2](https://index.ros.org/doc/ros2/) and the [`GAZEBO_MODEL_PATH`](http://gazebosim.org/tutorials?tut=components#EnvironmentVariables) for [SDFormat](http://sdformat.org/) enviromental variables are modified appropriatly.


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
export AMENT_PREFIX_PATH=${AMENT_PREFIX_PATH}:<prefix>
```
### Use the models with Gazebo
In order to use these models in Gazebo, set up the simulation environment following the instructions provided in the [icub-gazebo](https://github.com/robotology/icub-gazebo) repository, and add the following line to your ``.bashrc``:
```
export GAZEBO_MODEL_PATH=${GAZEBO_MODEL_PATH}:<prefix>/share/iCub/robots:<prefix>/share
```
Note that only the models that are known to work fine with the default physics engine settings of Gazebo (`iCubGazeboV2_5` and `iCubGazeboV2_5_plus`)
are installed. If you want to make available in Gazebo all the models, enable the `ICUB_MODELS_INSTALL_ALL_GAZEBO_MODELS` CMake option.

### Use the models from C++ helper library
In order to use these models in `c++` application you can exploit the `icub-models` library.
`icub-models` provides native `CMake` support which allows the library to be easily used in `CMake` projects.
**icub-models** exports a CMake target called `icub-models::icub-models` which can be imported using the `find_package` CMake command and used by calling `target_link_libraries` as in the following example:
```cmake
cmake_minimum_required(VERSION 3.0)
project(myproject)
find_package(icub-models REQUIRED)
add_executable(example example.cpp)
target_link_libraries(example icub-models::icub-models)
```

The `example.cpp` will contains
```cpp
#include <iCubModels/iCubModels.h>
#include <iostream>

int main()
{
    std::cout << "Models have been installed in: " << iCubModels::getModelsPath() << std::endl;

    std::cout << "Available robots: " << std::endl;
    for (const auto& robot : iCubModels::getRobotNames())
    {
        std::cout << " - " << robot << ": " <<  iCubModels::getModelFile(robot) << std::endl;
    }

    return EXIT_SUCCESS;
}
```

***Note: The ABI and the API of the C++ helper library has breaking changes only at major releases of the `icub-models` package.***

### Use the models from Python helper library
In order to use these models in `python` application you can exploit the `icub-models` module.
`icub-models` provides a `python` package to called `icub_models`. You can install it via `cmake`
```
cmake -DCMAKE_INSTALL_PREFIX=<path/where/you/want/to/install> \
      -DCMAKE_BUILD_TYPE=Release \
      -DICUB_MODELS_USES_PYTHON:BOOL=ON ..
cmake --build . --config Release --target install
```

Then the following script can be used to locate the models
```python
import icub_models

print(f"Models have been installed in: {icub_models.get_models_path()}")

print(f"Available robots: {icub_models.get_robot_names()}")

for robot_name in icub_models.get_robot_names():
    print(f"{robot_name}: {icub_models.get_model_file(robot_name)}")
```

## Change the orientation of the root frame
The iCub robot `root frame` is defined as [`x-backward`][1], meaning that the x-axis points behind the robot. Nevertheless, in the robotics community, sometimes the root frame of a robot is defined as [`x-forward`][2]. As a consequence, to use the iCub models with software developed for the `x-forward` configuration (e.g. [IHMC-ORS][3]), might be necessary to quickly update the root frame orientation.  
For this purpose, locate the joint `<joint name="base_fixed_joint" type="fixed">` in the `URDF` model and perform the following substitution in the `origin` section:

```
-  <origin xyz="0 0 0" rpy="0 -0 0"/>
+  <origin xyz="0 0 0" rpy="0 -0 3.14159265358979323846"/>
```

[1]:http://wiki.icub.org/wiki/ICubForwardKinematics
[2]:http://www.ros.org/reps/rep-0103.html#axis-orientation
[3]:https://github.com/ihmcrobotics/ihmc-open-robotics-software
