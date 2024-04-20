cmake_minimum_required(VERSION 3.10)

project(utf8_print LANGUAGES C)

set(CMAKE_C_STANDARD 99)
set(CMAKE_C_STANDARD_REQUIRED TRUE)

add_executable("${PROJECT_NAME}" utf8_print.c utf8.c utf8.h)
