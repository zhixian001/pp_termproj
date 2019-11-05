cmake_minimum_required(VERSION 3.0.0)
project(pp_termproj VERSION 0.1.0)

include(CTest)
enable_testing()

SET( CMAKE_RUNTIME_OUTPUT_DIRECTORY bin/ )
SET( LIBRARY_OUTPUT_PATH lib/ )


ADD_COMPILE_OPTIONS( -g -Wall -std=c++17)
INCLUDE_DIRECTORIES ( include )
LINK_DIRECTORIES ( lib /var/lib )
LINK_LIBRARIES ( GL GLU glut )
ADD_LIBRARY ( Bubblegame SHARED src/BaseObject.cpp src/Board.cpp src/Bubble.cpp src/Cannon.cpp src/Light.cpp src/Material.cpp src/VisualBoard.cpp )

LINK_LIBRARIES( Bubblegame )

add_executable(pp_termproj main.cpp)

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)
