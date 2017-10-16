cmake_minimum_required(VERSION 3.1)
project(spatialalgorithms LANGUAGES CXX C)
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED on)

option(BUILD_EXAMPLES "Build examples ON/OFF(default)" OFF)
option(WERROR "Add -Werror flag to build (turns warnings into errors)" ON)

# Enable extra warnings to adhere to https://github.com/mapbox/cpp/issues/37
set(DESIRED_WARNINGS "-Wall -Wextra -Wconversion -Wunreachable-code -Wuninitialized -pedantic-errors -Wold-style-cast -Wno-error=unused-variable -Wshadow -Wfloat-equal")
if(CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
  set(DESIRED_WARNINGS "${DESIRED_WARNINGS} -Weffc++")
elseif(CMAKE_CXX_COMPILER_ID STREQUAL "Clang")
  set(DESIRED_WARNINGS "${DESIRED_WARNINGS} -Wmost")
endif()

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${DESIRED_WARNINGS}")

if (WERROR)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Werror")
endif()

include(cmake/spatialalgorithms.cmake)
include(cmake/mason.cmake)

mason_use(boost VERSION 1.63.0 HEADER_ONLY)
mason_use(geometry VERSION 0.9.0 HEADER_ONLY)
mason_use(variant VERSION 1.1.4 HEADER_ONLY)
mason_use(wagyu VERSION 0.4.1 HEADER_ONLY)

include_directories("${PROJECT_SOURCE_DIR}/include")

set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} $ENV{LINKER_FLAGS}")
set(CMAKE_SHARED_LINKER_FLAGS "${CMAKE_SHARED_LINKER_FLAGS} $ENV{LINKER_FLAGS}")
set(CMAKE_MODULE_LINKER_FLAGS "${CMAKE_MODULE_LINKER_FLAGS} $ENV{LINKER_FLAGS}")

# clang LTO requires using llvm-ar and llvm-ranlib
if("${CMAKE_CXX_COMPILER_ID}" STREQUAL "Clang")
  find_program(LLVM_AR llvm-ar)
  find_program(LLVM_RANLIB llvm-ranlib)
  if ("${LLVM_AR}" STREQUAL "LLVM_AR-NOTFOUND" OR "${LLVM_RANLIB}" STREQUAL "LLVM_RANLIB-NOTFOUND")
    message(WARNING "LLVM specific binutils not found.")
  else()
    message(STATUS "Using LLVM specific binutils for LTO:")
    message(STATUS " ${LLVM_AR}")
    message(STATUS " ${LLVM_RANLIB}")
    set(CMAKE_AR ${LLVM_AR})
    set(CMAKE_RANLIB ${LLVM_RANLIB})
  endif()
endif()

file(GLOB_RECURSE Sources src src/*.cpp)

add_library(spatialalgorithms STATIC ${Sources})
target_include_directories(spatialalgorithms SYSTEM PRIVATE ${MASON_PACKAGE_boost_INCLUDE_DIRS})
target_include_directories(spatialalgorithms SYSTEM PUBLIC ${MASON_PACKAGE_geometry_INCLUDE_DIRS})
target_include_directories(spatialalgorithms SYSTEM PRIVATE ${MASON_PACKAGE_wagyu_INCLUDE_DIRS})
target_include_directories(spatialalgorithms SYSTEM PUBLIC ${MASON_PACKAGE_variant_INCLUDE_DIRS})

if(BUILD_EXAMPLES)
add_executable(hello-spatial-algorithms examples/hello-spatial-algorithms.cpp)
target_include_directories(hello-spatial-algorithms SYSTEM PRIVATE ${MASON_PACKAGE_boost_INCLUDE_DIRS})
target_include_directories(hello-spatial-algorithms SYSTEM PUBLIC ${MASON_PACKAGE_geometry_INCLUDE_DIRS})
target_include_directories(hello-spatial-algorithms SYSTEM PRIVATE ${MASON_PACKAGE_wagyu_INCLUDE_DIRS})
target_include_directories(hello-spatial-algorithms SYSTEM PUBLIC ${MASON_PACKAGE_variant_INCLUDE_DIRS})
target_link_libraries(hello-spatial-algorithms spatialalgorithms)
endif(BUILD_EXAMPLES)

file(GLOB_RECURSE Test_Sources test/unit test/unit/*.cpp)
add_executable(test_sa ${Test_Sources})
target_include_directories(test_sa SYSTEM PRIVATE ${MASON_PACKAGE_boost_INCLUDE_DIRS})
target_include_directories(test_sa SYSTEM PUBLIC ${MASON_PACKAGE_geometry_INCLUDE_DIRS})
target_include_directories(test_sa SYSTEM PRIVATE ${MASON_PACKAGE_wagyu_INCLUDE_DIRS})
target_include_directories(test_sa SYSTEM PUBLIC ${MASON_PACKAGE_variant_INCLUDE_DIRS})
target_link_libraries(test_sa spatialalgorithms)

install(DIRECTORY include DESTINATION .
                  FILES_MATCHING PATTERN "*.hpp")

set(install-targets)

list(APPEND install-targets spatialalgorithms test_sa)
if (BUILD_EXAMPLES)
   list(APPEND install-targets hello-spatial-algorithms)
endif (BUILD_EXAMPLES)

install(TARGETS ${install-targets}
        RUNTIME DESTINATION bin
        ARCHIVE DESTINATION lib)
