cmake_minimum_required(VERSION 3.20)
project(ex5_avikupinsky_master)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)

add_executable(ex5_avikupinsky_master
        Activation.cpp
        Activation.h
        Dense.cpp
        Dense.h
        Matrix.cpp
        Matrix.h
        MlpNetwork.cpp
        MlpNetwork.h)
