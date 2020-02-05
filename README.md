# pandorytool
A tool to automate ROM installation for the Pandora 3D

## How to compile
- Install MSYS2
- Start MSYS MINGW 64-Bit

```
pacman -Syu  # You'll have to close the terminal after this line
pacman -Su
pacman -S mingw-w64-x86_64-toolchain
pacman -S make
pacman -S mingw64/mingw-w64-x86_64-cmake
pacman -S msys/git
pacman -S mingw64/mingw-w64-x86_64-tinyxml2
git clone https://github.com/emuchicken/pandorytool.git
mkdir -p pandorytool/build
cd pandorytool/build
cmake -G "MinGW Makefiles" -DCMAKE_SH="CMAKE_SH-NOTFOUND" ..
cmake --build .
```