# Handle relocatability via reloc-cpp
option(ICUB_MODELS_USE_SYSTEM_RELOC_CPP "Use system reloc-cpp" OFF)
mark_as_advanced(ICUB_MODELS_USE_SYSTEM_RELOC_CPP)
if(ICUB_MODELS_USE_SYSTEM_RELOC_CPP)
  find_package(reloc-cpp REQUIRED)
else()
  include(FetchContent)
  FetchContent_Declare(
    reloc-cpp
    GIT_REPOSITORY https://github.com/ami-iit/reloc-cpp.git
    GIT_TAG        v0.1.0
  )
  FetchContent_MakeAvailable(reloc-cpp)
endif()

set(ICUB_MODELS_MODELS_RELATIVE_PATH share/iCub/robots)
configure_file(${CMAKE_CURRENT_SOURCE_DIR}/src/iCubModels.cpp.in
               ${CMAKE_CURRENT_BINARY_DIR}/autogenerated/iCubModels.cpp
               @ONLY)

set(LIBRARY_TARGET_NAME ${PROJECT_NAME})

# List of CPP (source) library files.
set(${LIBRARY_TARGET_NAME}_SRC
  ${CMAKE_CURRENT_BINARY_DIR}/autogenerated/iCubModels.cpp
)

# List of HPP (header) library files.
set(${LIBRARY_TARGET_NAME}_HDR
  ${CMAKE_CURRENT_SOURCE_DIR}/include/iCubModels/iCubModels.h
)


add_library(${LIBRARY_TARGET_NAME} ${${LIBRARY_TARGET_NAME}_SRC} ${${LIBRARY_TARGET_NAME}_HDR})

add_library(${PROJECT_NAME}::${LIBRARY_TARGET_NAME} ALIAS ${LIBRARY_TARGET_NAME})

set_target_properties(${LIBRARY_TARGET_NAME} PROPERTIES VERSION       ${${PROJECT_NAME}_VERSION}
                                                        PUBLIC_HEADER "${${LIBRARY_TARGET_NAME}_HDR}")

target_include_directories(${LIBRARY_TARGET_NAME} PUBLIC "$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>"
                                                         "$<INSTALL_INTERFACE:$<INSTALL_PREFIX>/${CMAKE_INSTALL_INCLUDEDIR}>")
                                                         
target_compile_features(${LIBRARY_TARGET_NAME} PUBLIC cxx_std_11)

reloc_cpp_generate(${LIBRARY_TARGET_NAME}
                   GENERATED_HEADER ${CMAKE_CURRENT_BINARY_DIR}/iCubModelsGetInstallPrefix.h
                   GENERATED_FUNCTION iCubModels::getInstallPrefix)
target_include_directories(${LIBRARY_TARGET_NAME} PRIVATE ${CMAKE_CURRENT_BINARY_DIR})

install(TARGETS ${LIBRARY_TARGET_NAME}
        EXPORT  ${PROJECT_NAME}
        LIBRARY       DESTINATION "${CMAKE_INSTALL_LIBDIR}"                            COMPONENT shlib
        ARCHIVE       DESTINATION "${CMAKE_INSTALL_LIBDIR}"                            COMPONENT lib
        RUNTIME       DESTINATION "${CMAKE_INSTALL_BINDIR}"                            COMPONENT bin
        PUBLIC_HEADER DESTINATION "${CMAKE_INSTALL_INCLUDEDIR}/iCubModels" COMPONENT dev)
