cmake_minimum_required(VERSION 3.14)
project(pandory)
set(CMAKE_CXX_STANDARD 17)

include_directories(/usr/local/include /usr/local/opt/libarchive/include)
link_directories(/usr/local/lib /usr/local/opt/libarchive/lib)

if ($ENV{JETBRAINS_IDE})
    set(JETBRAINS_CLION_IDE True CACHE BOOL "Build under CLion")
endif ($ENV{JETBRAINS_IDE})


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

#find_package(wxWidgets REQUIRED COMPONENTS net core base)


#if(MSVC OR MSYS OR MINGW)
#    if (NOT JETBRAINS_CLION_IDE)
#   option(CURL_STATICLIB "Set to ON to build libcurl with static linking."  ON)
#    add_definitions("-DCURL_STATICLIB")
#    endif()
#endif()

set(CURL_LIBRARY "-lcurl") 
find_package(CURL REQUIRED) 
include_directories(${CURL_INCLUDE_DIR})

if(MSVC OR MSYS OR MINGW)
    if (NOT JETBRAINS_CLION_IDE)
    # for detecting Windows compilers
    #set(DCMAKE_SH="CMAKE_SH-NOTFOUND")
    set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -O3 -static-libstdc++ -static -s")
    endif()
endif()

add_executable(
        pandory
        main.cpp
        src/CommandLineArguments.cpp
        src/CommandLineArguments.h
        src/PandoryTool.cpp
        src/PandoryTool.h
        src/modes/ModeAdd.cpp
        src/modes/ModeAdd.h
        src/Fs.cpp
        src/Fs.h
        src/McGamesXML.cpp
        src/McGamesXML.h
        src/SystemMapper.cpp
        src/SystemMapper.h
        src/McGamesTXT.cpp
        src/McGamesTXT.h
        src/McGamesAbstract.cpp
        src/McGamesAbstract.h
        src/modes/ModePrepare.cpp
        src/modes/ModePrepare.h
        src/modes/ModePspfix.cpp
        src/modes/ModePspfix.h
        src/modes/ModeStick.cpp
        src/modes/ModeStick.h
        src/libarchive.h
        src/StickExtractor.cpp
        src/StickExtractor.h
        src/definitions/PSPMapper.cpp
        src/definitions/PSPMapper.h
        src/types.h
        src/StickDownloader.cpp src/StickDownloader.h src/UserFolders.cpp src/UserFolders.h src/definitions/Sticks.cpp src/definitions/Sticks.h)

target_link_libraries(
    pandory
   

    archive
    tinyxml2
    iconv

    curl

    ssl 
    crypto 
    crypt32 
    gdi32 
    ws2_32
    
    ssh2
    idn2
    wldap32

    z

    # ${wxWidgets_LIBRARIES}
)
