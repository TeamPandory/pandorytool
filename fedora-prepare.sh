#!/bin/bash

# windows-build
sudo dnf install mingw64-gcc mingw64-gcc-c++ mingw64-winpthreads-static.noarch 

# linux-build
sudo dnf install gcc gcc-c++ tinyxml2.x86_64 tinyxml2-devel.x86_64

# generic build tools
sudo dnf install cmake make upx 

HERE=`pwd`

# Install mingw version of tinyxml
cd /tmp
wget https://github.com/leethomason/tinyxml2/archive/8.0.0.tar.gz
tar xvf 8.0.0.tar.gz
pushd tinyxml2-8.0.0/
mingw64-cmake . -DBUILD_SHARED_LIBS:BOOL=OFF -DBUILD_STATIC_LIBS:BOOL=ON
make && sudo make install
cd $HERE

