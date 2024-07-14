set(CMAKE_SYSTEM_NAME Generic)
set(CMAKE_SYSTEM_PROCESSOR i386)

set(CMAKE_C_COMPILER /usr/local/cross/bin/i386-pc-msdosdjgpp-gcc)
set(CMAKE_CXX_COMPILER /usr/local/cross/bin/i386-pc-msdosdjgpp-g++)
set(CMAKE_AR /usr/local/cross/bin/i386-pc-msdosdjgpp-ar)
set(CMAKE_STRIP /usr/local/cross/bin/i386-pc-msdosdjgpp-strip)


set(ENV{PKG_CONFIG_PATH} "/usr/local/cross/bin/i386-pc-msdosdjgpp-pkg-config")

set(CMAKE_C_FLAGS "")
set(CMAKE_CXX_FLAGS "")
set(CMAKE_EXE_LINKER_FLAGS "")