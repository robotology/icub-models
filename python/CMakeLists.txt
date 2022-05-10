# Copyright (C) 2022 Istituto Italiano di Tecnologia (IIT). All rights reserved.
# This software may be modified and distributed under the terms of the
# GNU Lesser General Public License v2.1 or any later version.

if(ICUB_MODELS_USES_PYTHON)

  find_package(Python3 COMPONENTS Interpreter REQUIRED)

  option(ICUB_MODELS_DETECT_ACTIVE_PYTHON_SITEPACKAGES
    "Do you want icub-models to detect and use the active site-package directory? (it could be a system dir)"
    FALSE)

    # Install the resulting Python package for the active interpreter
    if(ICUB_MODELS_DETECT_ACTIVE_PYTHON_SITEPACKAGES)
        set(PYTHON_INSTDIR ${Python3_SITELIB}/icub_models)
    else()
      execute_process(COMMAND ${Python3_EXECUTABLE} -c "from distutils import sysconfig; print(sysconfig.get_python_lib(1,0,prefix=''))"
        OUTPUT_VARIABLE _PYTHON_INSTDIR)

      string(STRIP ${_PYTHON_INSTDIR} _PYTHON_INSTDIR_CLEAN)
      set(PYTHON_INSTDIR ${_PYTHON_INSTDIR_CLEAN}/icub_models)
    endif()


    # Install the __init__.py file
    install(FILES "${CMAKE_CURRENT_SOURCE_DIR}/icub_models/__init__.py"
            DESTINATION ${PYTHON_INSTDIR})

    # Install the icub_models.py file inserting the relative path between
    # ${PYTHON_ABSOLUTE_INSTDIR} and ${CMAKE_INSTALL_DIR}
    if(IS_ABSOLUTE ${PYTHON_INSTDIR})
      set(PYTHON_ABSOLUTE_INSTDIR "${PYTHON_INSTDIR}")
    else()
      set(PYTHON_ABSOLUTE_INSTDIR "${CMAKE_INSTALL_PREFIX}/${PYTHON_INSTDIR}")
    endif()
    file(RELATIVE_PATH ICUB_MODELS_CXX_PYTHON_INSTALL_RELATIVE_DIR ${PYTHON_ABSOLUTE_INSTDIR} ${CMAKE_INSTALL_PREFIX})
    configure_file("${CMAKE_CURRENT_SOURCE_DIR}/icub_models/icub_models.py"
                   "${CMAKE_CURRENT_BINARY_DIR}/icub_models/icub_models.py"
                    @ONLY)
    install(FILES "${CMAKE_CURRENT_BINARY_DIR}/icub_models/icub_models.py"
            DESTINATION ${PYTHON_INSTDIR})

    # Install pip metadata files to ensure that icub_models installed via CMake is listed by pip list
    # See https://packaging.python.org/specifications/recording-installed-packages/
    # and https://packaging.python.org/en/latest/specifications/core-metadata/#core-metadata
    option(ICUB_MODELS_PYTHON_PIP_METADATA_INSTALL "Use CMake to install Python pip metadata. Set to off if some other tool already installs it." ON)
    mark_as_advanced(ICUB_MODELS_PYTHON_PIP_METADATA_INSTALL)
    set(ICUB_MODELS_PYTHON_PIP_METADATA_INSTALLER "cmake" CACHE STRING "Specify the string to identify the pip Installer. Default: cmake, change this if you are using another tool.")
    mark_as_advanced(ICUB_MODELS_PYTHON_PIP_METADATA_INSTALLER)
    if(ICUB_MODELS_PYTHON_PIP_METADATA_INSTALL)
      get_filename_component(PYTHON_METADATA_PARENT_DIR ${PYTHON_INSTDIR} DIRECTORY)
      if(WIN32)
        set(NEW_LINE "\n\r")
      else()
        set(NEW_LINE "\n")
      endif()
      file(WRITE ${CMAKE_CURRENT_BINARY_DIR}/METADATA "")
      file(APPEND ${CMAKE_CURRENT_BINARY_DIR}/METADATA "Metadata-Version: 2.1${NEW_LINE}")
      file(APPEND ${CMAKE_CURRENT_BINARY_DIR}/METADATA "Name: icub-models${NEW_LINE}")
      file(APPEND ${CMAKE_CURRENT_BINARY_DIR}/METADATA "Version: ${PROJECT_VERSION}${NEW_LINE}")
      file(WRITE ${CMAKE_CURRENT_BINARY_DIR}/INSTALLER "${ICUB_MODELS_PYTHON_PIP_METADATA_INSTALLER}${NEW_LINE}")
      install(
        FILES "${CMAKE_CURRENT_BINARY_DIR}/METADATA" "${CMAKE_CURRENT_BINARY_DIR}/INSTALLER"
        DESTINATION ${PYTHON_METADATA_PARENT_DIR}/icub_models-${PROJECT_VERSION}.dist-info)
    endif()

endif()
