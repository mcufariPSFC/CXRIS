#ifndef IMAGEPLATE_H
#define IMAGEPLATE_H
#include <vector>
#include <utility>
#include "ray.hpp"
#include "pixel.hpp"


class ImagePlate{
public:

    ImagePlate(int nx, int ny, int IPID, double beginE, double endE, int nE, double extX, double exY, double standOff, int refine);
    
    void printCoordList();
    void UpdatePSLUsingPSLperPhoton(int ix, int jy, Ray xray);
    int get_nx();
    int get_ny();
    double get_beginE();
    double get_endE();
    int get_nE();
    std::pair<double,double> get_coords(int i, int j);
    double get_standOff();

    void write(int i, int j, Ray r);
    double get_PSL(int i, int j);
    std::vector<Pixel*> get_tree();

private:
    double beginE; //Beginning of IP energy sensitivity keV
    double endE; // End of IP energy sensitivity (- range/nE technically) keV
    double nE; //number of energy bins

    int nx;
    int ny;
    std::vector<Pixel*> IPPixelTree;
    std::vector<std::pair<double,double> >  IPPixelCoords;
    std::vector<double> PSL;
    
    double extX;
    double extY;
    double standOff;
    int IPID;

    int refine;

};
void MakeStack(std::vector<ImagePlate*>& ipStack, int camID);
#endif