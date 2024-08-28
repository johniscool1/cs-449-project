# Linux & FreeBSD Compilation
```
mkdir build
cd build
cmake ..
make
```
Executable is in bin/
# Windows Compilation
```
mkdir build
cd build
cmake ..
cmake --build .
```
Executable is in bin/Debug/

Note: When building on windows, the cmake options to not build the FLTK library's example programs are for some reason ignored.
