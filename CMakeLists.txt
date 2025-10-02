cmake_minimum_required(VERSION 4.0)
project(BTreeCSV_Cplusplus)

set(CMAKE_CXX_STANDARD 26)

add_executable(BTreeCSV_Cplusplus main.cpp
        csvManager.cpp
        csvManager.h)
