# Download and unpack googletest at configure time
include(FetchContent)

FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/release-1.11.0.zip
)

# For Windows: Prevent overriding the parent project's compiler/linker settings
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)

# FetchContent_MakeAvailable will automatically download and add GoogleTest to the build
FetchContent_MakeAvailable(googletest)

# Add test executable
add_executable(test-events "test-events.cpp")

# Link test executable against GoogleTest and the serialiser library
target_link_libraries(test-events gtest_main events-lib)

# Include GoogleTest CMake module
include(GoogleTest)
gtest_discover_tests(test-events)

# Set the output directories for the build
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
