
message(STATUS "Updating submodules...")
execute_process(
    COMMAND git submodule update --init
    WORKING_DIRECTORY "${CMAKE_SOURCE_DIR}")

# CMake 3.1 does not have this yet.
set(CMAKE_CXX11_STANDARD_COMPILE_OPTION "-std=c++11")
set(CMAKE_CXX11_EXTENSION_COMPILE_OPTION "-std=gnu++11")
