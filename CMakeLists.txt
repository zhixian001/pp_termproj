cmake_minimum_required(VERSION 3.0.0)
project(Bubblebobble_Termproject_28 VERSION 0.1.0)

include(CTest)
enable_testing()

SET ( PROJECT_ROOT_DIRECTORY  Bubblebobble_Termproject_28)



SET( CMAKE_RUNTIME_OUTPUT_DIRECTORY bin/ )
SET( LIBRARY_OUTPUT_PATH lib/ )


ADD_COMPILE_OPTIONS( -g -Wall -std=c++17)
INCLUDE_DIRECTORIES ( "${PROJECT_ROOT_DIRECTORY}/include" )
LINK_DIRECTORIES ( lib /var/lib )
LINK_LIBRARIES ( GL GLU glut freeimage )
ADD_LIBRARY ( Bubblegame SHARED "${PROJECT_ROOT_DIRECTORY}/src/BaseObject.cpp" "${PROJECT_ROOT_DIRECTORY}/src/Board.cpp" "${PROJECT_ROOT_DIRECTORY}/src/Bubble.cpp" "${PROJECT_ROOT_DIRECTORY}/src/Cannon.cpp" "${PROJECT_ROOT_DIRECTORY}/src/Light.cpp" "${PROJECT_ROOT_DIRECTORY}/src/Material.cpp" "${PROJECT_ROOT_DIRECTORY}/src/VisualBoard.cpp" "${PROJECT_ROOT_DIRECTORY}/src/Texts.cpp" "${PROJECT_ROOT_DIRECTORY}/src/TimeBar.cpp")

LINK_LIBRARIES( Bubblegame )

add_executable(Bubblebobble_Termproject_28 "${PROJECT_ROOT_DIRECTORY}/src/run.cpp")

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)
