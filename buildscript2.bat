@echo off
echo Start build!
@echo on
g++ -Iinclude\ -I"C:\MinGW\freeglut\include" -L"C:\MinGW\freeglut\lib" -Lsrc -c src\WireShape3D.cpp -o build\WireShape3D.o -lopengl32 -lfreeglut -lglu32 -Wl,--subsystem,windows
g++ -Iinclude\ -I"C:\MinGW\freeglut\include" -L"C:\MinGW\freeglut\lib" -Lsrc -c src\WireSphere.cpp -o build\WireSphere.o -lopengl32 -lfreeglut -lglu32 -Wl,--subsystem,windows
g++ -Iinclude\ -I"C:\MinGW\freeglut\include" -L"C:\MinGW\freeglut\lib" -Lsrc -c src\WireTeapot.cpp -o build\WireTeapot.o -lopengl32 -lfreeglut -lglu32 -Wl,--subsystem,windows
g++ -Iinclude\ -I"C:\MinGW\freeglut\include" -L"C:\MinGW\freeglut\lib" -Lsrc -c src\WireTorus.cpp -o build\WireTorus.o -lopengl32 -lfreeglut -lglu32 -Wl,--subsystem,windows
g++ -I"C:\MinGW\freeglut\include" -I"include" -Lsrc -L"C:\MinGW\freeglut\lib" "src\run.cpp" -g "build\WireSphere.o" -g "build\WireTorus.o" -g "build\WireTeapot.o" -g "build\WireShape3D.o" -o run.exe -Wall -lopengl32 -lfreeglut -lglu32 -Wl,--subsystem,windows
@echo off
echo End of Build Script
@echo on
