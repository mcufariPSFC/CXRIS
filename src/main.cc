#include "../include/camera.hpp"
int main(){
    Camera cam;
    Grid g;
    cam.beginRayTrace(g);
    cam.outRayTrace();
    return 0;
}
