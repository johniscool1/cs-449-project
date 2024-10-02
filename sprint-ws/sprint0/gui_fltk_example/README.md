# Linux & FreeBSD Compilation
```
mkdir build
cd build
cmake ..
make
```
Executable is in bin/
# Windows Compilation
WILL ONLY COMPILE ON WINDOWS 10 (COMPILING ON WINDOWS 11 WILL COMPLE, BUT CAUSE PROGRAM TO CRASH) I have inclued the binaries in the release to avoid this.

open visual studio code, in the top menu click view->terminal
```
mkdir build
cd build
cmake ..
cmake --build .
```
Executable is in bin/Debug/

Note: When building on windows, the cmake options to not build the FLTK library's example programs are for some reason ignored.
