cmake_minimum_required(VERSION 3.1)
project(spatialalgorithms LANGUAGES CXX C)
set(CMAKE_CXX_STANDARD 14)

include(cmake/spatialalgorithms.cmake)
include(cmake/mason.cmake)

mason_use(boost VERSION 1.63.0 HEADER_ONLY)
#mason_use(boost_libtest VERSION 1.63.0)
mason_use(geometry VERSION 0.9.0 HEADER_ONLY)
mason_use(variant VERSION 1.1.4 HEADER_ONLY)
mason_use(wagyu VERSION 0.4.1 HEADER_ONLY)

include_directories("${PROJECT_SOURCE_DIR}/include")

file(GLOB_RECURSE Sources src src/*.cpp)

add_library(spatialalgorithms ${Sources})
target_include_directories(spatialalgorithms SYSTEM PRIVATE ${MASON_PACKAGE_boost_INCLUDE_DIRS})
target_include_directories(spatialalgorithms SYSTEM PUBLIC ${MASON_PACKAGE_geometry_INCLUDE_DIRS})
target_include_directories(spatialalgorithms SYSTEM PRIVATE ${MASON_PACKAGE_wagyu_INCLUDE_DIRS})
target_include_directories(spatialalgorithms SYSTEM PUBLIC ${MASON_PACKAGE_variant_INCLUDE_DIRS})

file(GLOB_RECURSE Test_Sources test/unit test/unit/*.cpp)
add_executable(test_sa ${Test_Sources})
target_include_directories(test_sa SYSTEM PRIVATE ${MASON_PACKAGE_boost_INCLUDE_DIRS})
target_include_directories(test_sa SYSTEM PUBLIC ${MASON_PACKAGE_geometry_INCLUDE_DIRS})
target_include_directories(test_sa SYSTEM PRIVATE ${MASON_PACKAGE_wagyu_INCLUDE_DIRS})
target_include_directories(test_sa SYSTEM PUBLIC ${MASON_PACKAGE_variant_INCLUDE_DIRS})
target_link_libraries(test_sa spatialalgorithms)
