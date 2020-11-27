# Changelog
All notable changes to this project will be documented in this file.

The format of this document is based on [Keep a Changelog](https://keepachangelog.com/en/1.0.0/).

## [Unreleased]

## [1.18.0] - 2020-11-30

### Added
- Added first URDF model for the iCub3, namely the `iCubGazeboV3`  with inertia modified to run in Gazebo Classic, and iCubGenova09 for control of the real robot. 
  As the development of this model is an ongoing activity, interested users are suggested to keep in sync with the updates that will happen in the `devel` branch. 

### Changed
- The `base_link` massless link is now a child of the `root_link` link instead of being a parent. This has the effect that now when the URDF model of iCub is imported
  in Gazebo, after fixed joint lumping the link corresponding to the robot waist will be `root_link`, instead of `base_link`. This means that when the iCub model is included 
  in a nested model, the joint to connect it to the rest of the model should refer to `iCub::root_link` instead of `iCub::base_link`
  (https://github.com/robotology/icub-models-generator/pull/142, https://github.com/robotology/icub-models-generator/issues/140#issuecomment-700653608).
