cmake_minimum_required(VERSION 3.15)
project(projeto C)

set(CMAKE_C_STANDARD 99)

add_executable(projeto main.c interface.c interface.h dados.c dados.h logica.c logica.h)