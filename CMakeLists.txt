cmake_minimum_required(VERSION 3.15)
project(pandory)
set(CMAKE_CXX_STANDARD 14)
add_executable(pandory main.cpp src/CommandLineArguments.cpp src/CommandLineArguments.h src/PandoryTool.cpp src/PandoryTool.h src/modes/ModeAdd.cpp src/modes/ModeAdd.h src/FileSystem.cpp src/FileSystem.h)