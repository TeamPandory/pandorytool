cmake_minimum_required(VERSION 3.14)
project(pandory)
set(CMAKE_CXX_STANDARD 17)

include_directories(/usr/local/include)
link_directories(/usr/local/lib)

if(MSVC OR MSYS OR MINGW)
    # for detecting Windows compilers
    set(DCMAKE_SH="CMAKE_SH-NOTFOUND")
    set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -O3 -static-libstdc++ -static -s")
endif()

add_executable(pandory main.cpp src/CommandLineArguments.cpp src/CommandLineArguments.h src/PandoryTool.cpp src/PandoryTool.h src/modes/ModeAdd.cpp src/modes/ModeAdd.h src/Fs.cpp src/Fs.h src/McGamesXML.cpp src/McGamesXML.h src/SystemMapper.cpp src/SystemMapper.h)

target_link_libraries(
    pandory
    tinyxml2
)