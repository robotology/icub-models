# Copyright: (C) 2017 Fondazione Istituto Italiano di Tecnologia
# Authors: Silvio Traversaro
# CopyPolicy: Released under the terms of the LGPLv2.1 or later, see LGPL.TXT

cmake_minimum_required(VERSION 2.8.9)

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
file(COPY ${CMAKE_SOURCE_DIR}/iCub DESTINATION ${CMAKE_BINARY_DIR})

# Generate and move in the build tree the model.config for each robot
SUBDIRLIST(ROBOTS_NAMES ${CMAKE_BINARY_DIR}/iCub/robots)
foreach (ROBOT_DIRNAME ${ROBOTS_NAMES})
  set(ROBOT_NAME ${ROBOT_DIRNAME})
  configure_file(${CMAKE_SOURCE_DIR}/model.config.in
                 ${CMAKE_BINARY_DIR}/iCub/robots/${ROBOT_NAME}/model.config
                 @ONLY)
endforeach()

# Install the whole iCub directory
install(DIRECTORY ${CMAKE_BINARY_DIR}/iCub DESTINATION share)
