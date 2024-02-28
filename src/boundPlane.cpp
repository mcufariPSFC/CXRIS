#include "../include/boundPlane.hpp"

BoundPlane::BoundPlane(double* vert1, double* vert2, double* vert3, double* vert4):
vert1(vert1),
vert2(vert2),
vert3(vert3),
vert4(vert4)
{

}

double* BoundPlane::testIntersection(double* origin, double* direction){
    
    return 0;
}
bool BoundPlane::isPointInSide(double* pt){
    return false;
}
