cmake_minimum_required(VERSION 3.15)
project(native_pspfix)

set(CMAKE_CXX_STANDARD 17)

add_executable(native_pspfix jni/main.cpp)