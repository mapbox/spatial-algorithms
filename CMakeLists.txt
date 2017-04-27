cmake_minimum_required(VERSION 3.1)
project(spatialalgorithms LANGUAGES CXX)
set(CMAKE_CXX_STANDARD 14)

include(cmake/spatialalgorithms.cmake)
include(cmake/mason.cmake)

mason_use(boost VERSION 1.63.0 HEADER_ONLY)
mason_use(variant VERSION 1.1.4 HEADER_ONLY)
mason_use(wagyu VERSION 0.4.1 HEADER_ONLY)
