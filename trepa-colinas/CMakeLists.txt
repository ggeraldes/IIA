cmake_minimum_required(VERSION 3.24)
project(trepa_colinas C)

set(CMAKE_C_STANDARD 11)

include_directories(.)

add_executable(Nova_pasta
        algoritmo.c
        algoritmo.h
        funcao.c
        funcao.h
        main.c
        utils.c
        utils.h)
