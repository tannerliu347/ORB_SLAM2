cmake_minimum_required(VERSION 2.8)
project(DBoW2)

set(LIBRARY_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/lib)

add_library(cnpy SHARED cnpy.cpp)