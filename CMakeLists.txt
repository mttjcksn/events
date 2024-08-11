cmake_minimum_required(VERSION 3.10)
project(events)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Add the header-only library
add_library(events-lib INTERFACE)
target_include_directories(events-lib INTERFACE src)

set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -g")

# Define option for building tests, defaulting to ON if the project is the top-level project
if(CMAKE_SOURCE_DIR STREQUAL PROJECT_SOURCE_DIR)    
    enable_testing()
    add_subdirectory(test)
else()
    option(BUILD_TESTS "Build tests" OFF)
endif()


