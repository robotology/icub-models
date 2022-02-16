# Copyright (C) 2022 Istituto Italiano di Tecnologia (IIT). All rights reserved.
# This software may be modified and distributed under the terms of the
# GNU Lesser General Public License v2.1 or any later version.

pybind11_add_module(pybind11_icub_models MODULE
  ${CMAKE_CURRENT_SOURCE_DIR}/icub_models.cpp
  )

target_include_directories(pybind11_icub_models PUBLIC "$<BUILD_INTERFACE:${pybind_include_dirs}>")

target_link_libraries(pybind11_icub_models PRIVATE
  icub-models::icub-models)

# # The generated Python dynamic module must have the same name as the pybind11
# # module, i.e. `bindings`.
set_target_properties(pybind11_icub_models PROPERTIES
    LIBRARY_OUTPUT_DIRECTORY "${ICUB_MODELS_PYTHON_PACKAGE}"
    OUTPUT_NAME "bindings")


# Output package is:
#
# icub_models
# |-- __init__.py (generated from main bindings CMake file)
# `-- bindings.<cpython_extension>

install(TARGETS pybind11_icub_models DESTINATION ${PYTHON_INSTDIR})
