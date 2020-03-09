cmake_minimum_required(VERSION 3.14)
project(pandory)
set(CMAKE_CXX_STANDARD 17)

include_directories(/usr/local/include)
link_directories(/usr/local/lib)

execute_process(
        COMMAND git log -1 --format=%h
        WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}
        OUTPUT_VARIABLE GIT_COMMIT_HASH
        OUTPUT_STRIP_TRAILING_WHITESPACE
)
add_definitions("-DGIT_COMMIT_HASH=\"${GIT_COMMIT_HASH}\"")

if($ENV{NO_SHAREWARE_LIMIT})
add_definitions("-DNO_SHAREWARE_LIMIT=1")
endif()

if(MSVC OR MSYS OR MINGW)
    # for detecting Windows compilers
    set(DCMAKE_SH="CMAKE_SH-NOTFOUND")
    set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -O3 -static-libstdc++ -static -s")
endif()

add_executable(pandory main.cpp src/CommandLineArguments.cpp src/CommandLineArguments.h src/PandoryTool.cpp src/PandoryTool.h src/modes/ModeAdd.cpp src/modes/ModeAdd.h src/Fs.cpp src/Fs.h src/McGamesXML.cpp src/McGamesXML.h src/SystemMapper.cpp src/SystemMapper.h src/McGamesTXT.cpp src/McGamesTXT.h src/McGamesAbstract.cpp src/McGamesAbstract.h src/modes/ModePrepare.cpp src/modes/ModePrepare.h)

target_link_libraries(
    pandory
    tinyxml2
)