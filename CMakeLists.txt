cmake_minimum_required(VERSION 3.5)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)
set(CMAKE_C_COMPILER /usr/local/bin/gcc-13)
set(CMAKE_CXX_COMPILER /usr/local/bin/g++-13)
set(CMAKE_CXX_FLAGS "-O3 -Wall -Wextra -fopenmp")


project(CXRIS)


set(SRC_DIR SRC/)

add_executable(
    cxris
    src/main.cpp
    src/boundPlane.cpp 
    src/boundingShell.cpp 
    src/boundingShellCollection.cpp 
    src/pixel.cpp 
    src/aperatureGrid.cpp 
    src/aperatureList.cpp 
    src/imagePlate.cpp 
    src/ray.cpp 
    src/grid.cpp
    src/camera.cpp 
)


