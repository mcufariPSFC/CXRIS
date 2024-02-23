HEADERS = include/aperatureGrid.hpp include/aperatureList.hpp include/imagePlate.hpp include/ray.hpp include/grid.hpp include/camera.hpp 
SRC = include/aperatureGrid.cpp include/aperatureList.cpp include/imagePlate.cpp include/ray.cpp include/grid.cpp include/camera.cpp 


default:
	g++ $(HEADERS) $(SRC) src/main.cc -Wall