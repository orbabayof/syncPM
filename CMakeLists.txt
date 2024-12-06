cmake_minimum_required(VERSION 3.31)
project(syncpm)

set(CMAKE_CXX_STANDARD 20)

add_executable(syncpm main.cpp
        constants.h
        color.h
        util/util.cpp
        util/util.h
        packageManager/packageManager.cpp
        packageManager/packageManager.h)
