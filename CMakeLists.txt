# Copyright: (C) 2017 Fondazione Istituto Italiano di Tecnologia
# Authors: Silvio Traversaro
# CopyPolicy: Released under the terms of the LGPLv2.1 or later, see LGPL.TXT

cmake_minimum_required(VERSION 3.5)

project(icub-models)

macro(SUBDIRLIST result curdir)
  file(GLOB children RELATIVE ${curdir} ${curdir}/*)
  set(dirlist "")
  foreach(child ${children})
    if(IS_DIRECTORY ${curdir}/${child})
      list(APPEND dirlist ${child})
    endif()
  endforeach()
  set(${result} ${dirlist})
endmacro()

# Copy the iCub folder in the build tree
file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/iCub DESTINATION ${CMAKE_CURRENT_BINARY_DIR})

# Copy the ros folder
file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/ros DESTINATION ${CMAKE_CURRENT_BINARY_DIR}/iCub)

# Add the model.config just for a limited number of models that are known
# to work in Gazebo, unless the ICUB_MODELS_INSTALL_ALL_GAZEBO_MODELS option
# is enabled
option(ICUB_MODELS_INSTALL_ALL_GAZEBO_MODELS OFF)

# Note: all the models run in Gazebo, but this two are the only one that
# run with the default physics settings of Gazebo, see issue
# https://github.com/robotology/icub-model-generator/issues/52 for more info
set(GAZEBO_SUPPORTED_MODELS "")
list(APPEND GAZEBO_SUPPORTED_MODELS "iCubGazeboV2_5")
list(APPEND GAZEBO_SUPPORTED_MODELS "iCubGazeboV2_5_plus")

SUBDIRLIST(ROBOTS_NAMES ${CMAKE_CURRENT_BINARY_DIR}/iCub/robots)
foreach (ROBOT_DIRNAME ${ROBOTS_NAMES})
  set(ROBOT_NAME ${ROBOT_DIRNAME})
  set(ROBOT_MODEL_CONFIG_FILE "${CMAKE_CURRENT_BINARY_DIR}/iCub/robots/${ROBOT_NAME}/model.config")
  set(ROBOT_FIXED_MODEL_FOLDER "${CMAKE_CURRENT_BINARY_DIR}/iCub/robots/${ROBOT_NAME}_fixed")
  set(ROBOT_FIXED_MODEL_CONFIG_FILE "${ROBOT_FIXED_MODEL_FOLDER}/model.config")
  set(ROBOT_FIXED_MODEL_SDF_FILE "${ROBOT_FIXED_MODEL_FOLDER}/${ROBOT_NAME}_fixed.sdf")

  if(ROBOT_NAME IN_LIST GAZEBO_SUPPORTED_MODELS OR ICUB_MODELS_INSTALL_ALL_GAZEBO_MODELS)
    configure_file(${CMAKE_CURRENT_SOURCE_DIR}/model.config.in
                   ${ROBOT_MODEL_CONFIG_FILE}
                   @ONLY)

    file(MAKE_DIRECTORY ${ROBOT_FIXED_MODEL_FOLDER})

    configure_file(${CMAKE_CURRENT_SOURCE_DIR}/fixed_model.config.in
                   ${ROBOT_FIXED_MODEL_CONFIG_FILE}
                   @ONLY)
    configure_file(${CMAKE_CURRENT_SOURCE_DIR}/fixed_model.sdf.in
                   ${ROBOT_FIXED_MODEL_SDF_FILE}
                   @ONLY)
  else()
    # Cleanup is before ICUB_MODELS_INSTALL_ALL_GAZEBO_MODELS was set to ON
    file(REMOVE ${ROBOT_MODEL_CONFIG_FILE})
    file(REMOVE_RECURSE ${ROBOT_FIXED_MODEL_FOLDER})
  endif()

endforeach()

# Install the whole iCub directory
install(DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/iCub DESTINATION share)
