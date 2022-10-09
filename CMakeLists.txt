cmake_minimum_required(VERSION 3.20)
project(autoaccept C)

set(CMAKE_C_STANDARD 99)

add_executable(autoaccept main.c autoaccept.c autoaccept.h)
#add_executable(autoaccept WIN32 main.c autoaccept.c autoaccept.h)