#ifndef APERATUREGRID_H
#define APERATUREGRID_H
#include <string>
#include <vector>
#include <utility>

class AperatureGrid{
public:

    AperatureGrid();
    AperatureGrid(int nx, int ny, std::string geo, double radius, double xoffset, double yoffset, double zoffset);
    
    int get_nx();
    int get_ny();
    std::vector<std::pair<double,double> > get_aperatureGridCenters();
    std::pair<double,double> get_coords(int i, int j);
    double get_zoffset();
private:
    int nx;
    int ny;
    double zoffset;
    std::vector<std::pair<double,double> > aperatureGridCenters;

};
#endif 