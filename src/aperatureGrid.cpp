#include "../include/aperatureGrid.hpp"
#include <fstream>
#include <iostream>
using namespace std;


AperatureGrid::AperatureGrid(int nx, int ny, string geo, double radius, double xoffset, double yoffset, double zoffset):
nx(nx),
ny(ny),
zoffset(zoffset)
{

    /*Find centers of semi-rectangular cells of equal area
    Algorithm description: Slice azimuthally such that there are ny slices. Slice radially such that
    1/(nx+1) = ((ri+delta)^2-ri^2))/R^2. That is, find the radii that slice the pie wedge into equally partitions

    Note that the i'th radial slice depends on the i-1 others before it. This process can only be parallelized along the azimuth

    */
   double dtheta = 2.0 * M_PI / (double) ny;
   double theta = 0.0;
   double rad = 0.0;
   double drad = radius / nx;
   std::vector<std::pair<double,double> > grid;
    for (int i = 0; i < nx; i++){
        for (int j = 0; j < ny; j++){
            std::pair<double,double> coords((double) xoffset + rad * sin(theta),yoffset + rad * cos(theta));
            grid.push_back(coords);
            //drad = -1.0 * rad + sqrt(rad*rad + radius*radius / (double) (nx));
            theta += dtheta;
        }
        theta = 0;
        rad += drad;
    }
    aperatureGridCenters = grid;

}

int AperatureGrid::get_nx(){
    return nx;
}
int AperatureGrid::get_ny(){
    return ny;
}
std::vector<std::pair<double,double> > AperatureGrid::get_aperatureGridCenters(){
    return aperatureGridCenters;
}

std::pair<double,double> AperatureGrid::get_coords(int i, int j){
    return aperatureGridCenters[ny * i + j];
}

double AperatureGrid::get_zoffset(){
    return zoffset;
}