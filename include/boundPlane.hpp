#ifndef BOUNDPLANE_H
#define BOUNDPLANE_H


class BoundPlane{
public:
    
    BoundPlane(double* vert1, double* vert2, double* vert3, double* vert4);
    
    //double* cross(double* a, double* b);

    bool isPointInSide(double* pt);
    double* testIntersection(double* origin, double* dir);
    
private:
    
    double* vert1;
    double* vert2;
    double* vert3;
    double* vert4;

}; 

#endif