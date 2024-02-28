#ifndef PIXEL_H
#define PIXEL_H
#include <iostream>
#include <vector>
#include <utility>
#include "ray.hpp"
/*
Pixel is an oct-tree structure that begins coarse to enable faster renders where rays do not intersect the grid

Note the neighbor structure is kept track of to ensure that the boundary of the image is precisely determined in high resolution

Pixel contains a flag when it is used in the ray-tracing algorithm that is set to 1 when the pixel has been traced at the current level.

The tracing algorithm populates a given pixel back onto the stack when it is refined either actively or passively

The tracing algorithm traces all refinement layers, and output is performed only at the finest grained

*/
class Pixel{
public:

    Pixel();
    Pixel(double xLoc, double yLoc, int level, double offsetX, double offsetY, int maxLevel);
    std::vector<Pixel*> refineActive(); //used when hit

    void add_PSL(Ray* r);
    

    Pixel* get_childTopLeft();
    Pixel* get_childTopRight();
    Pixel* get_childBottomRight();
    Pixel* get_childBottomLeft();
    Pixel* get_childBottom();
    Pixel* get_childLeft();
    Pixel* get_childRight();
    Pixel* get_childTop();
    
    std::pair<double,double> get_coords();
    int get_refined();
    int get_maxRefined();

    std::vector<std::pair<Pixel*, std::pair<double,double> > > traverse_coords();


    void print_pixel();
private:
    Pixel* childTopLeft;
    Pixel* childTopRight;
    Pixel* childBottomLeft;
    Pixel* childBottomRight;
    Pixel* childTop;
    Pixel* childBottom;
    Pixel* childLeft;
    Pixel* childRight;




    std::pair<double,double> coords;
    double PSL;

    double childOffsetX;
    double childOffsetY;

    int level;
    int maxLevel;
    int refined;
    int traced;
};
    std::vector<std::pair<Pixel*, std::pair<double,double> > > traverseCoordsHelper(Pixel* p);

#endif