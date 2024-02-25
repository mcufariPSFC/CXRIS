HEADERS = include/boundingShell.hpp include/boundingShellCollection.hpp include/boundPlane.hpp include/pixel.hpp include/aperatureGrid.hpp include/aperatureList.hpp include/imagePlate.hpp include/ray.hpp include/grid.hpp include/camera.hpp 
SRC = include/boundPlane.cpp include/boundingShell.cpp include/boundingShellCollection.cpp include/pixel.cpp include/aperatureGrid.cpp include/aperatureList.cpp include/imagePlate.cpp include/ray.cpp include/grid.cpp include/camera.cpp 


default:
	g++-13 -O2 $(HEADERS) $(SRC) src/main.cc 