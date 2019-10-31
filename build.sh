#!/bin/bash

_TERM_COMMAND=""

if [ ! -d "$PWD/build" ]; then
    mkdir "$PWD/build"
    _TERM_COMMAND="rm -rf $PWD/build ; $_TERM_COMMAND"
else
    _TERM_COMMAND="rm -f build/Board.o ; $_TERM_COMMAND"
    _TERM_COMMAND="rm -f build/Bubble.o ; $_TERM_COMMAND"


fi


if [ ! -d "$PWD/lib" ]; then
    mkdir "$PWD/lib"
fi

if [ ! -d "$PWD/bin" ]; then
    mkdir "$PWD/bin"
fi


export LD_LIBRARY_PATH="$PWD/lib:$LD_LIBRARY_PATH"
g++ -fPIC -Iinclude/ -c src/Bubble.cpp -o build/Bubble.o -Wall
g++ -fPIC -Iinclude/ -c src/Board.cpp -o build/Board.o -Wall

# g++ -shared -Wl,-soname,libLight.so -o lib/libLight.so build/Light.o 
# g++ -shared -Wl,-soname,libMaterial.so -o lib/libMaterial.so build/Material.o 

# g++ -shared -Wl,-soname,libSolidShape3D.so -o lib/libSolidShape3D.so build/SolidShape3D.o build/Material.o build/Light.o
# g++ -shared -Wl,-soname,libSolidTorus.so -o lib/libSolidTorus.so build/SolidTorus.o build/Material.o build/Light.o build/SolidShape3D.o
# g++ -shared -Wl,-soname,libSolidTeapot.so -o lib/libSolidTeapot.so build/SolidTeapot.o build/Material.o build/Light.o build/SolidShape3D.o
# g++ -shared -Wl,-soname,libSolidSphere.so -o lib/libSolidSphere.so build/SolidSphere.o build/Material.o build/Light.o build/SolidShape3D.o

g++ -shared -Wl,-soname,libBubblegame.so -o lib/libBubblegame.so build/Board.o build/Bubble.o


g++ -Llib -Iinclude/ src/run.cpp -o bin/_run -Wall -lGL -lGLU -lglut -lBubblegame

eval "$_TERM_COMMAND"

exit