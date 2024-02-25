#ifndef BOUNDPLANE_H
#define BOUNDPLANE_H


class BoundPlane{
public:
    
    BoundPlane(double* verts);
    BoundPlane();
    
    bool isPointInSide(double* pt);
private:
    
    double* verts;

}; 

#endif