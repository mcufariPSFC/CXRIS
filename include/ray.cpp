#include "ray.hpp"
#include <iostream>
Ray::Ray(){
    unitDirection[0] = 0.0;
    unitDirection[1] = 0.0;
    unitDirection[2] = 1.0;

    coordinateOfLaunch[0] = 0.0;
    coordinateOfLaunch[1] = 0.0;
    coordinateOfLaunch[2] = 0.0;

    std::vector<double> temp(1,0.0);
    energySpectrum = temp;
}

void Ray::updateRayDir(std::pair<double,double> IPPixelCoords, double IPStand, std::pair<double,double> apGridCoords, double apGridStand, double* xBasis, double* yBasis, double* zbasis){
    double IPCenter[3];
    IPCenter[0] = zbasis[0] * IPStand;
    IPCenter[1] = zbasis[1] * IPStand;
    IPCenter[2] = zbasis[2] * IPStand;

    double apCenter[3];
    apCenter[0] = zbasis[0] * apGridStand;
    apCenter[1] = zbasis[1] * apGridStand;
    apCenter[2] = zbasis[2] * apGridStand;

    double rayBase[3];
    rayBase[0] = IPCenter[0] + xBasis[0] * IPPixelCoords.first + yBasis[0]*IPPixelCoords.second;
    rayBase[1] = IPCenter[1] + xBasis[1] * IPPixelCoords.first + yBasis[1]*IPPixelCoords.second;
    rayBase[2] = IPCenter[2] + xBasis[2] * IPPixelCoords.first + yBasis[2]*IPPixelCoords.second;

    double rayTarget[3];

    rayTarget[0] = apCenter[0] + xBasis[0] * apGridCoords.first + yBasis[0] * apGridCoords.second;
    rayTarget[1] = apCenter[1] + xBasis[1] * apGridCoords.first + yBasis[1] * apGridCoords.second;
    rayTarget[2] = apCenter[2] + xBasis[2] * apGridCoords.first + yBasis[2] * apGridCoords.second;

    double rayDir[3];

    rayDir[0] = rayTarget[0]-rayBase[0];
    rayDir[1] = rayTarget[1]-rayBase[1];
    rayDir[2] = rayTarget[2]-rayBase[2];

    double rayDirNorm = sqrt(rayDir[0]*rayDir[0]+rayDir[1]*rayDir[1]+rayDir[2]*rayDir[2]);

    unitDirection[0] = rayDir[0] / rayDirNorm;
    unitDirection[1] = rayDir[1] / rayDirNorm;
    unitDirection[2] = rayDir[2] / rayDirNorm;

    coordinateOfLaunch[0] = rayBase[0];
    coordinateOfLaunch[1] = rayBase[1];
    coordinateOfLaunch[2] = rayBase[2];
}

void Ray::updateRaySpec(int nE){
    std::vector<double> temp(nE,0.0);
    energySpectrum = temp;
}

std::pair<double*, int> Ray::launchRay(Grid* g, double beginE, double endE, int nE){
    double udoto = dot(unitDirection,coordinateOfLaunch);
    double udoto2 = udoto*udoto;
    double usq = dot(unitDirection,unitDirection);
    double osq = dot(coordinateOfLaunch, coordinateOfLaunch);
    double disc = udoto2 - usq * (osq - g->get_boundingSphere().back()->get_outR() * g->get_boundingSphere().back()->get_outR());
    double coordIntersect[3] = {0.0,0.0,0.0};
    if(disc < 0){
        return std::make_pair(coordIntersect,0);
    }
    else{
        return std::make_pair(coordIntersect,1);
    }
    
}

double Ray::get_spectrum(){
    return energySpectrum[0];
}

double dot(double* a, double* b){
    return a[0]*b[0]+a[1]*b[1]+a[2]*b[2];
}