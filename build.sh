#!/bin/bash

_TERM_COMMAND=""

if [ ! -d "$PWD/build" ]; then
    mkdir "$PWD/build"
    _TERM_COMMAND="rm -rf $PWD/build ; $_TERM_COMMAND"
else
    _TERM_COMMAND="rm -f build/Light.o ; $_TERM_COMMAND"
    _TERM_COMMAND="rm -f build/Board.o ; $_TERM_COMMAND"
    _TERM_COMMAND="rm -f build/Bubble.o ; $_TERM_COMMAND"
    _TERM_COMMAND="rm -f build/Cannon.o ; $_TERM_COMMAND"
fi

if [ ! -d "$PWD/lib" ]; then
    mkdir "$PWD/lib"
fi

if [ ! -d "$PWD/bin" ]; then
    mkdir "$PWD/bin"
fi

export LD_LIBRARY_PATH="$PWD/lib:$LD_LIBRARY_PATH"
g++ -fPIC -Iinclude/ -c src/Light.cpp -o build/Light.o -Wall
g++ -fPIC -Iinclude/ -c src/Bubble.cpp -o build/Bubble.o -Wall
g++ -fPIC -Iinclude/ -c src/Board.cpp -o build/Board.o -Wall
g++ -fPIC -Iinclude/ -c src/Cannon.cpp -o build/Cannon.o -Wall

g++ -shared -Wl,-soname,libBubblegame.so -o lib/libBubblegame.so build/Board.o build/Bubble.o build/Cannon.o build/Light.o

g++ -Llib -Iinclude/ src/run.cpp -o bin/_run -Wall -lGL -lGLU -lglut -lBubblegame

eval "$_TERM_COMMAND"

exit