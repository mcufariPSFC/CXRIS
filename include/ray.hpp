#ifndef RAY_H
#define RAY_H
#include <vector>
#include "grid.hpp"
#include <cmath>
class Ray{
public:
    Ray();
    void updateRayDir(std::pair<double,double> IPPixelCoords, double IPStand, std::pair<double,double> apGridCoords, double apGridStand, double* xBasis, double* yBasis, double* zbasis); //initialze the ray by reading in the inputFile and computing the initial position

    void updateRaySpec(int nE);
    
    void launchRay(Grid G, double beginE, double endE, int nE); //compute energy spectrum along ray given the grid G

    double get_spectrum();


private:
    std::vector<double> energySpectrum;
    double unitDirection[3];

    double coordinateOfLaunch[3];

};

double dot(double* a, double* b);

#endif