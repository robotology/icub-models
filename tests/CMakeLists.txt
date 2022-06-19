# SPDX-FileCopyrightText: Fondazione Istituto Italiano di Tecnologia (IIT)
# SPDX-License-Identifier: LGPL-2.1-or-later

# Test dependencies
find_package(Gazebo REQUIRED)
find_package(GazeboYARPPlugins REQUIRED)
find_package(YARP REQUIRED)

include(FetchContent)

FetchContent_Declare(
  gazebo-classic-gtest
  GIT_REPOSITORY https://github.com/robotology-dependencies/gazebo-classic-gtest.git
  GIT_TAG         gazebo11_11.3.0
)

FetchContent_GetProperties(gazebo-classic-gtest)
if(NOT gazebo-classic-gtest_POPULATED)
  FetchContent_Populate(gazebo-classic-gtest)
  add_library(icub-models-gazebo-classic-gtest STATIC ${gazebo-classic-gtest_SOURCE_DIR}/src/gtest-all.cc)
  target_include_directories(icub-models-gazebo-classic-gtest PUBLIC ${gazebo-classic-gtest_SOURCE_DIR} ${gazebo-classic-gtest_SOURCE_DIR}/include)
endif()

add_executable(iCubModelsGazeboClassicSmokeTest iCubModelsGazeboClassicSmokeTest.cc)
target_include_directories(iCubModelsGazeboClassicSmokeTest PUBLIC ${GAZEBO_INCLUDE_DIRS})
find_library(GAZEBO_TEST_LIB NAMES gazebo_test_fixture HINTS ${GAZEBO_LIBRARY_DIRS})
target_link_libraries(iCubModelsGazeboClassicSmokeTest PUBLIC ${GAZEBO_TEST_LIB} icub-models-gazebo-classic-gtest ${Boost_LIBRARIES} YARP::YARP_dev ${GAZEBO_LIBRARIES})
# We pass information to the test to make sure that it can find the models
target_compile_definitions(iCubModelsGazeboClassicSmokeTest PRIVATE -DPROJECT_BINARY_DIR="${PROJECT_BINARY_DIR}")
message(STATUS "PROJECT_BINARY_DIR: ${PROJECT_BINARY_DIR}")
add_test(NAME iCubModelsGazeboClassicSmokeTest COMMAND iCubModelsGazeboClassicSmokeTest)
# Ensure that YARP devices can be found
set_property(TEST iCubModelsGazeboClassicSmokeTest PROPERTY ENVIRONMENT YARP_DATA_DIRS=${YARP_DATA_INSTALL_DIR_FULL})


