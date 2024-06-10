cmake_minimum_required(VERSION 3.28)
project(EP1 C)

set(CMAKE_C_STANDARD 11)

include_directories(.)

add_executable(EP1
        driverEP1.c
        EP1.c)
