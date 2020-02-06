# pandorytool
A tool to automate ROM installation for the Pandora 3D

## License
pandorytool is "shareware", licensed under the Attribution-NonCommercial-ShareAlike 4.0 International (CC BY-NC-SA 4.0). If you wish to use pandorytool commercially, exceptions to this license are available from @emuchicken.


## How to compile
- Install MSYS2
- Start MSYS MINGW 64-Bit

## Install dependencies
```
pacman -Syu  # You'll have to close the terminal after this line
pacman -Su
pacman -S mingw-w64-x86_64-toolchain
pacman -S make
pacman -S mingw64/mingw-w64-x86_64-cmake
pacman -S msys/git
pacman -S mingw64/mingw-w64-x86_64-tinyxml2
```

## Clone and compile
```
git clone https://github.com/emuchicken/pandorytool.git
./winbuild.sh
```

Pandory will compile on other operating systems, such as MacOS/Linux, as long as you have a gcc toolchain and the relevant libraries installed.
