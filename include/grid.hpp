#ifndef GRID_H
#define GRID_H
#include <vector>

/* The grid class contains a the hydrodynamic information for the post-processed image */
/* The grid is spherical, must be cut into wedges at r=0 such that no r=0 exclusion zone exists */
/* The grid enables the tracing of rays from the source (the image plate plane) through to the end of the grid*/
/* See the ray class for an understanding of how the ray-trace works*/

/* The grid class necessitates the grid_input.txt file in inputs*/
/*A comprehensive guide to such files is not available at this time*/

class Grid{
public:
    
    Grid();
    
    
    /*std::vector<double> plasmaThermalBremm(int nr, int ntheta, int nphi);
    
    int get_nr();
    int get_ntheta();
    int get_nphi() ;*/

    double get_maxRadius();
private:
    int nr;
    int ntheta;
    int nphi;
    std::vector<double> electronTemp; //value of electron temp in a given cell
    std::vector<double> ionTemp;    //value of ion temp in a given cell
    std::vector<double> ionDensity; //value of ion density in a given cell
    std::vector<double> electronDensity; //value of electron density in a given cell

    double maxRadiusCm; //maximum radius of grid
    
};
#endif

