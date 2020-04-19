#!/bin/bash

# windows-build
sudo dnf -y install mingw32-gcc mingw32-gcc-c++ mingw32-winpthreads-static.noarch mingw32-win-iconv-static.noarch

# linux-build
sudo dnf -y install gcc gcc-c++ tinyxml2.x86_64 tinyxml2-devel.x86_64

# generic build tools
sudo dnf -y install cmake make upx 

HERE=`pwd`

# Install mingw version of tinyxml
cd /tmp
wget https://github.com/leethomason/tinyxml2/archive/8.0.0.tar.gz
tar xvf 8.0.0.tar.gz
pushd tinyxml2-8.0.0/
mingw32-cmake . -DBUILD_SHARED_LIBS:BOOL=OFF -DBUILD_STATIC_LIBS:BOOL=ON
make && sudo make install

cd /tmp
wget https://github.com/libarchive/libarchive/releases/download/v3.4.2/libarchive-3.4.2.tar.gz
tar xvf libarchive-3.4.2.tar.gz
pushd libarchive-3.4.2/
mingw32-configure --without-lzma --without-xml2 --without-expat --without-libb2 --without-openssl --without-bz2lib --without-cng
make && sudo make install


cd $HERE

