# Changelog
All notable changes to this project will be documented in this file.

The format of this document is based on [Keep a Changelog](https://keepachangelog.com/en/1.0.0/).

## [Unreleased]

## [1.22.0] - 2021-11-12

### Changed
* Update iCub3 with feet covers (https://github.com/robotology/icub-models-generator/pull/210).
* Increase metacarpus joint limit of MK3 left hand's thumb (https://github.com/robotology/icub-models-generator/pull/211).

### Fixed
* Fixed compatibility of all iCub3 models with gazebo-yarp-plugins 4 (https://github.com/robotology/icub-models-generator/pull/21).

## [1.21.1] - 2021-09-03

### Fixed
* Fixed document on the use of `AMENT_PREFIX_PATH` environment variable (https://github.com/robotology/icub-models/pull/101).
* Fixed wrong default collision on the arms that slowed down Gazebo Classic simulation for iCub3 models (https://github.com/robotology/icub-models/issues/100, https://github.com/robotology/icub-models-generator/pull/208).

## [1.21.0] - 2021-08-27

### Added
* The `hand_mk3` and `wrist_mk2` containing the new version of iCub's hand and wrist, codenamed iCub hand Mk3 and iCub wrist Mk2, have been added to the repo. As this models are still in development, they could change in the future (https://github.com/robotology/icub-models-generator/pull/203, https://github.com/robotology/icub-models/pull/95).

### Changed
* The iCub3 models (`iCubGenova09` and `iCubGazeboV3`) have been updated with the new arm covers (https://github.com/robotology/icub-models-generator/pull/202).

### Fixed 
* The masses of iCub3 models (`iCubGenova09` and `iCubGazeboV3`) have been fixed to be more similar to the one of the real robot (https://github.com/robotology/icub-models-generator/pull/207).


## [1.20.0] - 2021-05-30

### Changed
* The gains and damping parameters of `iCubGazeboV3` have been changed (https://github.com/robotology/icub-models-generator/pull/199).

## [1.19.0] - 2021-02-24

### Added 
- Added documentation to use the models in ROS2 (https://github.com/robotology/icub-models/pull/82).
- Added model for the iCubErzelli02 robot (https://github.com/robotology/icub-models-generator/pull/195).

### Fixed 
- Fixed the license tag in the package.xml for use the models in ROS/ROS2 (https://github.com/robotology/icub-models/pull/78).
- Fixed several issues and problems with the iCubGenova09/iCubGazeboV3 model (https://github.com/robotology/icub-models-generator/pull/194, https://github.com/robotology/icub-models-generator/pull/193, https://github.com/robotology/icub-models-generator/pull/189, https://github.com/robotology/icub-models-generator/pull/187). 

## [1.18.1] - 2020-11-30

### Fixed 
- Fix the direction of some axis for the iCub3 models (https://github.com/robotology/icub-models-generator/pull/184). 

## [1.18.0] - 2020-11-30

### Added
- Added first URDF model for the iCub3, namely the `iCubGazeboV3`  with inertia modified to run in Gazebo Classic, and iCubGenova09 for control of the real robot. 
  As the development of this model is an ongoing activity, interested users are suggested to keep in sync with the updates that will happen in the `devel` branch. 

### Changed
- The `base_link` massless link is now a child of the `root_link` link instead of being a parent. This has the effect that now when the URDF model of iCub is imported
  in Gazebo, after fixed joint lumping the link corresponding to the robot waist will be `root_link`, instead of `base_link`. This means that when the iCub model is included 
  in a nested model, the joint to connect it to the rest of the model should refer to `iCub::root_link` instead of `iCub::base_link`
  (https://github.com/robotology/icub-models-generator/pull/142, https://github.com/robotology/icub-models-generator/issues/140#issuecomment-700653608).
