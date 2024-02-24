#include "../include/camera.hpp"
#include <iostream>
int main(){
    Camera cam;
    Grid g;
    std::cout << "begin trace " << std::endl;
    cam.beginRayTrace(g);
    std::cout << "End trace" << std::endl;
    return 0;
}
