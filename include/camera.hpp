#ifndef CAMERA_H
#define CAMERA_H

#include "aperatureGrid.hpp"
#include "aperatureList.hpp"
#include "grid.hpp"
#include "imagePlate.hpp"
#include "ray.hpp"
#include <string>

    /* The camera class provides necessary functionality to "image" a scene*/
    /* The detection media are image plates which contain the individual pixels*/
    /* Note that the rays keep track of the spectrum (in the fully-finished version of this code)*/
    /* and as such, the IP-pixel reduces the ray-spectrum information at the conclusion of a post-processing*/
    /* The camera contains an image plate stack and an aperature list*/
    /* The image plate stack is necessary for understanding the properties of the x-ray images as they form on IPS with different filtering*/

class Camera{
public:

    Camera(); //Constructor class that reads in the camera_input file
    void outputFirstIPCoords();
    void beginRayTrace(Grid* g);
    void outRayTrace();
private:
    AperatureList cameraAperatureList;
    double cameraPositionCart[3];
    double camUnitVec[3];
    double xBasisVectorInImagePlane[3];
    double yBasisVectorInImagePlane[3];

    int cameraID;

   

    std::vector<ImagePlate*> IPStack;

};
#endif