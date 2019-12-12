cmake_minimum_required(VERSION 3.14)

project(smapstool)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

add_executable(smapstool
    main.cc
    smapstool.cc
    stringutility.cc
)
