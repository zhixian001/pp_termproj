#!/bin/bash

_TERM_COMMAND=""

if [ ! -d "$PWD/build" ]; then
    mkdir "$PWD/build"
    _TERM_COMMAND="rm -rf $PWD/build ; $_TERM_COMMAND"
else
    _TERM_COMMAND="rm -f build/SolidSphere.o ; $_TERM_COMMAND"
    _TERM_COMMAND="rm -f build/SolidTeapot.o ; $_TERM_COMMAND"
    _TERM_COMMAND="rm -f build/SolidTorus.o ; $_TERM_COMMAND"
    _TERM_COMMAND="rm -f build/SolidShape3D.o ; $_TERM_COMMAND"
    _TERM_COMMAND="rm -f build/Light.o ; $_TERM_COMMAND"
    _TERM_COMMAND="rm -f build/Material.o ; $_TERM_COMMAND"


fi


if [ ! -d "$PWD/lib" ]; then
    mkdir "$PWD/lib"
fi

if [ ! -d "$PWD/bin" ]; then
    mkdir "$PWD/bin"
fi


export LD_LIBRARY_PATH="$PWD/lib:$LD_LIBRARY_PATH"
g++ -fPIC -Iinclude/ -c src/Light.cpp -o build/Light.o -Wall
g++ -fPIC -Iinclude/ -c src/Material.cpp -o build/Material.o -Wall
g++ -fPIC -Iinclude/ -c src/SolidShape3D.cpp -o build/SolidShape3D.o -Wall
g++ -fPIC -Iinclude/ -c src/SolidTorus.cpp -o build/SolidTorus.o -Wall
g++ -fPIC -Iinclude/ -c src/SolidTeapot.cpp -o build/SolidTeapot.o -Wall
g++ -fPIC -Iinclude/ -c src/SolidSphere.cpp -o build/SolidSphere.o -Wall

# g++ -shared -Wl,-soname,libLight.so -o lib/libLight.so build/Light.o 
# g++ -shared -Wl,-soname,libMaterial.so -o lib/libMaterial.so build/Material.o 

# g++ -shared -Wl,-soname,libSolidShape3D.so -o lib/libSolidShape3D.so build/SolidShape3D.o build/Material.o build/Light.o
# g++ -shared -Wl,-soname,libSolidTorus.so -o lib/libSolidTorus.so build/SolidTorus.o build/Material.o build/Light.o build/SolidShape3D.o
# g++ -shared -Wl,-soname,libSolidTeapot.so -o lib/libSolidTeapot.so build/SolidTeapot.o build/Material.o build/Light.o build/SolidShape3D.o
# g++ -shared -Wl,-soname,libSolidSphere.so -o lib/libSolidSphere.so build/SolidSphere.o build/Material.o build/Light.o build/SolidShape3D.o

g++ -shared -Wl,-soname,libSolids.so -o lib/libSolids.so build/SolidSphere.o build/SolidTeapot.o build/SolidTorus.o build/Material.o build/Light.o build/SolidShape3D.o


g++ -Llib -Iinclude/ src/run.cpp -o bin/_run -Wall -lGL -lGLU -lglut -lSolids

eval "$_TERM_COMMAND"

exit