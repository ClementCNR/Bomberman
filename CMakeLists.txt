cmake_minimum_required(VERSION 3.21)
project(Projet C)

set(CMAKE_C_STANDARD 99)

add_executable(Projet main.c lib/colors.h lib/colors.c lib/view.h lib/view.c lib/model.h lib/model.c lib/structs.h)
