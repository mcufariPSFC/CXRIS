#include "../include/boundPlane.hpp"

BoundPlane::BoundPlane(double* verts):
verts(verts)
{}
BoundPlane::BoundPlane(){
    
}
bool BoundPlane::isPointInSide(double* pt){
    return false;
}