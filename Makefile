HEADERS = include/aperatureGrid.hpp include/aperatureList.hpp include/imagePlate.hpp include/ray.hpp include/grid.hpp include/camera.hpp 
SRC = include/aperatureGrid.cpp include/aperatureList.cpp include/imagePlate.cpp include/ray.cpp include/grid.cpp include/camera.cpp 


default:
	g++-13 -O2 $(HEADERS) $(SRC) src/main.cc 