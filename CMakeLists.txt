cmake_minimum_required(VERSION 3.14)
project(pandory)
set(CMAKE_CXX_STANDARD 17)

if(MSVC OR MSYS OR MINGW)
    # for detecting Windows compilers
    set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -O3 -static -s")
endif()

add_executable(pandory main.cpp src/CommandLineArguments.cpp src/CommandLineArguments.h src/PandoryTool.cpp src/PandoryTool.h src/modes/ModeAdd.cpp src/modes/ModeAdd.h src/FileSystem.cpp src/FileSystem.h)

