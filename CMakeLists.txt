set(CMAKE_LEGACY_CYGWIN_WIN32 0) # Remove when CMake >= 2.8.4 is required
cmake_minimum_required(VERSION 2.6 FATAL_ERROR)

project(minisat)

#--------------------------------------------------------------------------------------------------
# Configurable options:
#include(CTest)
enable_testing()

option(STATIC_BINARIES "Link binaries statically." ON)
option(USE_SORELEASE   "Use SORELEASE in shared library filename." ON)

#--------------------------------------------------------------------------------------------------
# Library version:

set(MINISAT_SOMAJOR   2)
set(MINISAT_SOMINOR   1)
set(MINISAT_SORELEASE 0)

# Compute VERSION and SOVERSION:
if (USE_SORELEASE)
  set(MINISAT_VERSION ${MINISAT_SOMAJOR}.${MINISAT_SOMINOR}.${MINISAT_SORELEASE})
else()
  set(MINISAT_VERSION ${MINISAT_SOMAJOR}.${MINISAT_SOMINOR})
endif()
set(MINISAT_SOVERSION ${MINISAT_SOMAJOR})

#--------------------------------------------------------------------------------------------------
# Dependencies:

find_package(ZLIB)
include_directories(${ZLIB_INCLUDE_DIR})
include_directories(${minisat_SOURCE_DIR})

#--------------------------------------------------------------------------------------------------
# Compile flags:

add_definitions(-D__STDC_FORMAT_MACROS -D__STDC_LIMIT_MACROS)

#--------------------------------------------------------------------------------------------------
# Build Targets:

set(MINISAT_LIB_SOURCES
    minisat/utils/Options.cc
    minisat/utils/System.cc
    minisat/core/Solver.cc
    minisat/simp/SimpSolver.cc)

add_library(minisat-lib-static STATIC ${MINISAT_LIB_SOURCES})
add_library(minisat-lib-shared SHARED ${MINISAT_LIB_SOURCES})

target_link_libraries(minisat-lib-shared ${ZLIB_LIBRARY})
target_link_libraries(minisat-lib-static ${ZLIB_LIBRARY})

add_executable(minisat_core minisat/core/Main.cc)
add_executable(minisat_simp minisat/simp/Main.cc)

add_test(test1 echo --help)

if(STATIC_BINARIES)
  target_link_libraries(minisat_core minisat-lib-static)
  target_link_libraries(minisat_simp minisat-lib-static)
else()
  target_link_libraries(minisat_core minisat-lib-shared)
  target_link_libraries(minisat_simp minisat-lib-shared)
endif()

set_target_properties(minisat-lib-static PROPERTIES OUTPUT_NAME "minisat")
set_target_properties(minisat-lib-shared
  PROPERTIES
    OUTPUT_NAME "minisat" 
    VERSION ${MINISAT_VERSION}
    SOVERSION ${MINISAT_SOVERSION})

set_target_properties(minisat_simp       PROPERTIES OUTPUT_NAME "minisat")

#--------------------------------------------------------------------------------------------------
# Installation targets:

install(TARGETS minisat-lib-static minisat-lib-shared minisat_core minisat_simp 
        RUNTIME DESTINATION bin
        LIBRARY DESTINATION lib
        ARCHIVE DESTINATION lib)

install(DIRECTORY minisat/mtl minisat/utils minisat/core minisat/simp
        DESTINATION include/minisat
        FILES_MATCHING PATTERN "*.h")


#--------------------------------------------------------------------------------------------------
# Google test:


#find_program(
#        GIT_EXECUTABLE
#        NAMES git
#        DOC "git command line client"
#)
#mark_as_advanced(GIT_EXECUTABLE)
#
#include(FindPackageHandleStandardArgs)
#find_package_handle_standard_args(Git DEFAULT_MSG GIT_EXECUTABLE)
#
#
#
#find_package(Git)
#
#if(GIT_FOUND)
#  execute_process(
#          COMMAND ${GIT_EXECUTABLE} rev-list --max-count=1 HEAD
#          OUTPUT_VARIABLE GIT_REVISION
#          ERROR_QUIET
#  )
#  if(NOT ${GIT_REVISION} STREQUAL "")
#    string(STRIP ${GIT_REVISION} GIT_REVISION)
#  endif()
#  message(STATUS "Current git revision is ${GIT_REVISION}")
#else()
#  set(GIT_REVISION "unknown")
#endif()




set(GOOGLETEST_ROOT external/googletest/googletest CACHE STRING "Google Test source root")

message(STATUS "GOOGLETEST_ROOT set to ${GOOGLETEST_ROOT}")

# google test includes
include_directories(
        ${PROJECT_SOURCE_DIR}/${GOOGLETEST_ROOT}
        ${PROJECT_SOURCE_DIR}/${GOOGLETEST_ROOT}/include
)

# google test sources
set(GOOGLETEST_SOURCES
        ${PROJECT_SOURCE_DIR}/${GOOGLETEST_ROOT}/src/gtest-all.cc
        ${PROJECT_SOURCE_DIR}/${GOOGLETEST_ROOT}/src/gtest_main.cc
        )

# mark these files as generated (they may not be present at configure time)
foreach(_source ${GOOGLETEST_SOURCES})
  set_source_files_properties(${_source} PROPERTIES GENERATED 1)
endforeach()

add_library(googletest ${GOOGLETEST_SOURCES})



# target to update git submodules
add_custom_target(
        update_submodules
        COMMAND git submodule init
        COMMAND git submodule update
        WORKING_DIRECTORY ${PROJECT_SOURCE_DIR}
)

# update git submodules before building google test
add_dependencies(googletest update_submodules)

add_executable(runSimpleTests minisat/test/simple_test.cpp)
target_link_libraries(runSimpleTests googletest)
add_dependencies(runSimpleTests googletest)
if(STATIC_BINARIES)
  target_link_libraries(runSimpleTests minisat-lib-static)
else()
  target_link_libraries(runSimpleTests minisat-lib-shared)
endif()