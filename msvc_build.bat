@echo off

REM please execute this file in msvc x86 native compiler shell in current directory

call "C:\Program Files (x86)\Microsoft Visual Studio\2019\BuildTools\VC\Auxiliary\Build\vcvars32.bat"

call cd msvc
call cl /EHsc /Wall /std:c++17 "..\ab\ab\¼Ò½º.cpp" "..\ab\ab\BaseObject.cpp" "..\ab\ab\Board.cpp" "..\ab\ab\Bubble.cpp" "..\ab\ab\Cannon.cpp" "..\ab\ab\Light.cpp" "..\ab\ab\Material.cpp" "..\ab\ab\VisualBoard.cpp" "..\ab\ab\Texts.cpp"  /I "..\ab\ab" /I "include" "lib\glut32.lib" /link 

cd ..

PAUSE