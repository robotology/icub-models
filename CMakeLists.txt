# Copyright: (C) 2017 Fondazione Istituto Italiano di Tecnologia
# Authors: Silvio Traversaro
# CopyPolicy: Released under the terms of the LGPLv2.1 or later, see LGPL.TXT

cmake_minimum_required(VERSION 2.8.9)

project(icub-models)

# Install meshes 
install(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/iCub/meshes/simmechanics DESTINATION share/iCub/meshes)

# Install robots URDF files 
set(ROBOTS_TO_INSTALL "")
list(APPEND ROBOTS_TO_INSTALL "iCubGenova04")

foreach (robot ${ROBOTS_TO_INSTALL})
  install(FILES ${CMAKE_CURRENT_SOURCE_DIR}/iCub/robots/${robot}/model.urdf DESTINATION share/iCub/robots/${robot})
endforeach ()

# Install package.xml for ROS compatibility 
install(FILES ${CMAKE_CURRENT_SOURCE_DIR}/iCub/package.xml DESTINATION share/iCub)