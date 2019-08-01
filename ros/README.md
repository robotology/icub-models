This directory contains the files related to [Rviz](http://wiki.ros.org/rviz)
visualization of icub. The contents of this directory are installed inside `iCub`
ros package. The location of `iCub` ros pacakge is discovered by running `roscd iCub`.
The `launch` directory contains `roslaunch` file `iCubRviz.launch`. The robot model
that will be used for rviz visualization depends `YARP_ROBOT_NAME` set in `.bashrc`.
The default rviz configuration file is `iCubRviz.rviz` located inside `rviz` directory.
Rviz visualization of icub is launched by running

```
  roslaunch iCub iCubRviz.launch
```

The contents of this directory are tested on:

##### Linux

```
Ubuntu 18.04 LTS
Rosdistro: Melodic
Rosversion: 1.14.3
```

##### MacOS

```
MacOs High Sierra 10.13.6
Rosdistro: Lunar
Rosversion: 1.13.7
```
