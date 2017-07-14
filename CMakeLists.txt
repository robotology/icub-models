# Copyright: (C) 2017 Fondazione Istituto Italiano di Tecnologia
# Authors: Silvio Traversaro
# CopyPolicy: Released under the terms of the LGPLv2.1 or later, see LGPL.TXT

cmake_minimum_required(VERSION 2.8.9)

project(icub-models)

# Install the whole iCub directory
install(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/iCub DESTINATION share)

