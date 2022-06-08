# Copyright: (C) 2022 Fondazione Istituto Italiano di Tecnologia
# Authors: Silvio Traversaro
# CopyPolicy: Released under the terms of the LGPLv2.1 or later, see LGPL.TXT

cmake_minimum_required(VERSION 3.8)

project(icub-models
  VERSION 1.24.1)

include(GNUInstallDirs)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/${CMAKE_INSTALL_BINDIR}")
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/${CMAKE_INSTALL_LIBDIR}")
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/${CMAKE_INSTALL_LIBDIR}")

set(CMAKE_WINDOWS_EXPORT_ALL_SYMBOLS ON)
option(ICUB_MODELS_USES_PYTHON "Install the python package" OFF)


if(MSVC)
    set(CMAKE_DEBUG_POSTFIX "d")
endif()

set(CMAKE_C_EXTENSIONS OFF)
set(CMAKE_CXX_EXTENSIONS OFF)

list(APPEND CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/cmake)
option(BUILD_SHARED_LIBS "Build libraries as shared as opposed to static" ON)

# Enable RPATH support for installed binaries and libraries
include(AddInstallRPATHSupport)
add_install_rpath_support(BIN_DIRS "${CMAKE_INSTALL_FULL_BINDIR}"
                          LIB_DIRS "${CMAKE_INSTALL_FULL_LIBDIR}"
                          INSTALL_NAME_DIR "${CMAKE_INSTALL_FULL_LIBDIR}"
                          USE_LINK_PATH)

# Encourage user to specify a build type (e.g. Release, Debug, etc.), otherwise set it to Release.
if(NOT CMAKE_CONFIGURATION_TYPES)
    if(NOT CMAKE_BUILD_TYPE)
        message(STATUS "Setting build type to 'Release' as none was specified.")
        set_property(CACHE CMAKE_BUILD_TYPE PROPERTY VALUE "Release")
    endif()
endif()

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

# Copy the iCub_manual folder in the build tree
SUBDIRLIST(subdirs ${CMAKE_CURRENT_SOURCE_DIR}/iCub_manual)
foreach(subdir ${subdirs})
  file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/iCub_manual/${subdir}/ DESTINATION ${CMAKE_CURRENT_BINARY_DIR}/iCub/${subdir})
endforeach()

# Copy the ros folder
file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/ros DESTINATION ${CMAKE_CURRENT_BINARY_DIR}/iCub)

# Add the model.config just for a limited number of models that are known
# to work in Gazebo, unless the ICUB_MODELS_INSTALL_ALL_GAZEBO_MODELS option
# is enabled
option(ICUB_MODELS_INSTALL_ALL_GAZEBO_MODELS OFF)

set(ICUB_MODELS_SDF_VERSION "1.7")

# Note: all the models run in Gazebo, but this two are the only one that
# run with the default physics settings of Gazebo, see issue
# https://github.com/robotology/icub-model-generator/issues/52 for more info
set(GAZEBO_SUPPORTED_MODELS "")
list(APPEND GAZEBO_SUPPORTED_MODELS "iCubGazeboV2_5")
list(APPEND GAZEBO_SUPPORTED_MODELS "iCubGazeboV2_5_plus")
list(APPEND GAZEBO_SUPPORTED_MODELS "iCubGazeboV3")

# Note: these models don't need further configuration apart from 
# model version in model.config. Only one configuration is generated for
# these models, and no helper models (fixed, no_hans, and so on) are
# generated.
set(CONFIGURED_MODELS "")
list(APPEND CONFIGURED_MODELS "left_hand_mk3")
list(APPEND CONFIGURED_MODELS "left_wrist_mk2")

set(INSTALLED_URDF_MODELS "")

SUBDIRLIST(ROBOTS_NAMES ${CMAKE_CURRENT_SOURCE_DIR}/iCub/robots)
foreach(ROBOT_DIRNAME ${ROBOTS_NAMES})
  set(ROBOT_NAME ${ROBOT_DIRNAME})
  set(ROBOT_MODEL_CONFIG_FILE "${CMAKE_CURRENT_BINARY_DIR}/iCub/robots/${ROBOT_NAME}/model.config")

  set(ROBOT_FIXED_MODEL_FOLDER "${CMAKE_CURRENT_BINARY_DIR}/iCub/robots/${ROBOT_NAME}_fixed")
  set(ROBOT_FIXED_MODEL_CONFIG_FILE "${ROBOT_FIXED_MODEL_FOLDER}/model.config")
  set(ROBOT_FIXED_MODEL_SDF_FILE "${ROBOT_FIXED_MODEL_FOLDER}/${ROBOT_NAME}_fixed.sdf")

  set(ROBOT_FEET_FIXED_MODEL_FOLDER "${CMAKE_CURRENT_BINARY_DIR}/iCub/robots/${ROBOT_NAME}_feet_fixed")
  set(ROBOT_FEET_FIXED_MODEL_CONFIG_FILE "${ROBOT_FEET_FIXED_MODEL_FOLDER}/model.config")
  set(ROBOT_FEET_FIXED_MODEL_SDF_FILE "${ROBOT_FEET_FIXED_MODEL_FOLDER}/${ROBOT_NAME}_feet_fixed.sdf")

  list(APPEND INSTALLED_URDF_MODELS \"${ROBOT_NAME}\")

  if(ROBOT_NAME IN_LIST CONFIGURED_MODELS)
    configure_file(${CMAKE_CURRENT_SOURCE_DIR}/iCub/robots/${ROBOT_NAME}/model.config
                   ${CMAKE_CURRENT_BINARY_DIR}/iCub/robots/${ROBOT_NAME}/model.config
                   @ONLY)
  elseif(ROBOT_NAME IN_LIST GAZEBO_SUPPORTED_MODELS OR ICUB_MODELS_INSTALL_ALL_GAZEBO_MODELS)

    set(ROBOT_NAME_CONFIG "${ROBOT_NAME} (no hands)")
    set(ROBOT_MODEL_CONFIG "model.urdf")
    set(ROBOT_MODEL_DESCRIPTION_CONFIG "Model for the iCub humanoid robot. For more information check icub.org")
    configure_file(${CMAKE_CURRENT_SOURCE_DIR}/model.config.in
                   ${ROBOT_MODEL_CONFIG_FILE}
                   @ONLY)

    file(MAKE_DIRECTORY ${ROBOT_FIXED_MODEL_FOLDER})
    set(ROBOT_NAME_CONFIG "${ROBOT_NAME}_fixed (no hands)")
    set(ROBOT_MODEL_CONFIG "${ROBOT_NAME}_fixed.sdf")
    set(ROBOT_MODEL_DESCRIPTION_CONFIG "Model for the iCub humanoid robot, fixed on the air. For more information check icub.org")
    configure_file(${CMAKE_CURRENT_SOURCE_DIR}/model.config.in
                   ${ROBOT_FIXED_MODEL_CONFIG_FILE}
                   @ONLY)
    configure_file(${CMAKE_CURRENT_SOURCE_DIR}/fixed_model.sdf.in
                   ${ROBOT_FIXED_MODEL_SDF_FILE}
                   @ONLY)

    file(MAKE_DIRECTORY ${ROBOT_FEET_FIXED_MODEL_FOLDER})
    set(ROBOT_NAME_CONFIG "${ROBOT_NAME}_feet_fixed (no hands)")
    set(ROBOT_MODEL_CONFIG "${ROBOT_NAME}_feet_fixed.sdf")
    set(ROBOT_MODEL_DESCRIPTION_CONFIG "Model for the iCub humanoid robot, with the feet fixed on the ground. For more information check icub.org")
    configure_file(${CMAKE_CURRENT_SOURCE_DIR}/model.config.in
                   ${ROBOT_FEET_FIXED_MODEL_CONFIG_FILE}
                   @ONLY)
    configure_file(${CMAKE_CURRENT_SOURCE_DIR}/feet_fixed_model.sdf.in
                   ${ROBOT_FEET_FIXED_MODEL_SDF_FILE}
                   @ONLY)
  else()
    # Cleanup is before ICUB_MODELS_INSTALL_ALL_GAZEBO_MODELS was set to ON
    file(REMOVE ${ROBOT_MODEL_CONFIG_FILE})
    file(REMOVE_RECURSE ${ROBOT_FIXED_MODEL_FOLDER})
    file(REMOVE_RECURSE ${ROBOT_FEET_FIXED_MODEL_FOLDER})
  endif()
endforeach()

# Deal with manually generated models
set(GAZEBO_SUPPORTED_MODELS "")
list(APPEND GAZEBO_SUPPORTED_MODELS "iCubGazeboV2_5_visuomanip")

SUBDIRLIST(ROBOTS_NAMES ${CMAKE_CURRENT_SOURCE_DIR}/iCub_manual/robots)
foreach(ROBOT_NAME ${ROBOTS_NAMES})
  if(ROBOT_NAME IN_LIST GAZEBO_SUPPORTED_MODELS)
    configure_file(${CMAKE_CURRENT_SOURCE_DIR}/iCub_manual/robots/${ROBOT_NAME}/model.config
                   ${CMAKE_CURRENT_BINARY_DIR}/iCub/robots/${ROBOT_NAME}/model.config
                   @ONLY)
  endif()
endforeach()


SUBDIRLIST(ROBOTS_NAMES ${CMAKE_CURRENT_SOURCE_DIR}/iCub_manual/robots)
foreach(ROBOT_NAME ${ROBOTS_NAMES})

  list(APPEND INSTALLED_URDF_MODELS \"${ROBOT_NAME}\")

  if(ROBOT_NAME IN_LIST GAZEBO_SUPPORTED_MODELS)
    configure_file(${CMAKE_CURRENT_SOURCE_DIR}/iCub_manual/robots/${ROBOT_NAME}/model.config
                   ${CMAKE_CURRENT_BINARY_DIR}/iCub/robots/${ROBOT_NAME}/model.config
                   @ONLY)
  endif()
endforeach()

string(REPLACE ";" "," INSTALLED_URDF_MODELS "${INSTALLED_URDF_MODELS}")

# Install the whole iCub directory
install(DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/iCub DESTINATION share)

add_subdirectory(cpp)
add_subdirectory(python)

include(InstallBasicPackageFiles)
install_basic_package_files(${PROJECT_NAME}
                            VERSION ${${PROJECT_NAME}_VERSION}
                            COMPATIBILITY AnyNewerVersion
                            VARS_PREFIX ${PROJECT_NAME}
                            NO_CHECK_REQUIRED_COMPONENTS_MACRO)

include(AddUninstallTarget)
