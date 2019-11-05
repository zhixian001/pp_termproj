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
    _TERM_COMMAND="rm -f build/Material.o ; $_TERM_COMMAND"
    _TERM_COMMAND="rm -f build/BaseObject.o ; $_TERM_COMMAND"
    _TERM_COMMAND="rm -f build/VisualBoard.o ; $_TERM_COMMAND"

fi

if [ ! -d "$PWD/lib" ]; then
    mkdir "$PWD/lib"
fi

if [ ! -d "$PWD/bin" ]; then
    mkdir "$PWD/bin"
fi

export LD_LIBRARY_PATH="$PWD/lib:$LD_LIBRARY_PATH"
g++ -fPIC -Iinclude/ -c src/Light.cpp -o build/Light.o -Wall -std=c++17
g++ -fPIC -Iinclude/ -c src/Bubble.cpp -o build/Bubble.o -Wall -std=c++17
g++ -fPIC -Iinclude/ -c src/Board.cpp -o build/Board.o -Wall -std=c++17
g++ -fPIC -Iinclude/ -c src/Cannon.cpp -o build/Cannon.o -Wall -std=c++17
g++ -fPIC -Iinclude/ -c src/Material.cpp -o build/Material.o -Wall -std=c++17
g++ -fPIC -Iinclude/ -c src/BaseObject.cpp -o build/BaseObject.o -Wall -std=c++17
g++ -fPIC -Iinclude/ -c src/VisualBoard.cpp -o build/VisualBoard.o -Wall -std=c++17



g++ -std=c++17 -shared -Wl,-soname,libBubblegame.so -o lib/libBubblegame.so build/Board.o build/Bubble.o build/Cannon.o build/Light.o build/Material.o build/VisualBoard.o build/BaseObject.o

g++ -std=c++17 -Llib -Iinclude/ src/run.cpp -o bin/_run -Wall -lGL -lGLU -lglut -lBubblegame

eval "$_TERM_COMMAND"

exit