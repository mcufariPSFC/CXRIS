#ifndef BOUNDINGSHELL_H
#define BOUNDINGSHELL_H

#include "boundPlane.hpp"
#include "ray.hpp"
class BoundingShell{
public:

    BoundingShell(double inny, double outy, int maxRefine, int curLevel, double ctheta, double cphi);
    BoundingShell* findLowestChildIntersection(double* intersect);

    void print_memberCoords(int levelDes);
    
   
    void set_exitInterior(BoundingShell* bs);
    void set_exitExterior(BoundingShell* bs);
    void set_exitPlusTheta(BoundingShell* bs);
    void set_exitMinusTheta(BoundingShell* bs);
    void set_exitMinusPhi(BoundingShell* bs);
    void set_exitPlusPhi(BoundingShell* bs);

    void propagateHit(Ray r, double* intPt);

private:
    
    BoundingShell* uthetauphi; // Recurvisevly defined structure containing higher resolution grid elements
    BoundingShell* uthetalphi;
    BoundingShell* lthetauphi;
    BoundingShell* lthetalphi;

    double dtheta;
    double dphi;
    double centerTheta;
    double centerPhi;
    double innerR;
    double outerR;
    int maxRefine;
    int level;

    const double physProp = 1.0; //Note to Matt: add physical properties to bottom layer at some point

    BoundingShell* exitInterior;
    BoundingShell* exitExterior;
    BoundingShell* exitPlusTheta;
    BoundingShell* exitMinusTheta;
    BoundingShell* exitPlusPhi;
    BoundingShell* exitMinusPhi;


    
};

#endif