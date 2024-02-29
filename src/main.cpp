#include "../include/camera.hpp"
#include <iostream>
int main(){
    Camera cam;
    Grid* g = new Grid();
    //std::cout << "begin trace " << std::endl;
    cam.beginRayTrace(g);
    //std::cout << "End trace" << std::endl;
    //cam.outRayTrace();
    return 0;
}
