cmake_minimum_required(VERSION 3.8)
project(os_project2A)

set(CMAKE_C_STANDARD 99)

set(SOURCE_FILES main.c source/part3/part3.c source/part4/part4.c)
add_executable(os_project2A ${SOURCE_FILES})