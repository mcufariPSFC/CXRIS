#include "../include/aperatureList.hpp"
#include "../include/aperatureGrid.hpp"
#include <string>
#include <fstream>
#include <iostream>
#include <utility>
using namespace std;

AperatureList::AperatureList(){
   nAps = -1;
}

void AperatureList::create(int CamID){
    ifstream aperature_in("../inputs/aperatures_input.txt");
    
    string testString;
    nAps = 0;
    double radius;
    double xoffset;
    double yoffset;
    double zoffset;
    string geo;
    int cidTest = -2;
    while (aperature_in >> testString){

       if (testString == "APERATURE"){
        aperature_in >> cidTest;
        if(cidTest == CamID){
            int nx = 10;
            int ny = 10;
            string geo = "Circle";
            radius = 1;
            xoffset = 0;
            yoffset = 0;
            zoffset = 0;
            nAps++;
            while(aperature_in >> testString){
                if (testString == "END"){
                    break;
                }
                if (testString == "geo"){
                    aperature_in >> geo;
                }
                if (testString == "radius"){
                    aperature_in >> radius;
                }
                if (testString == "nx"){
                    aperature_in >> nx;
                }
                if (testString == "ny"){
                    aperature_in >> ny;
                }

                if (testString == "xoffset"){
                    aperature_in >> xoffset;
                }
                
                if (testString == "yoffset"){
                    aperature_in >> yoffset;
                }
                if (testString == "zoffset"){
                    aperature_in >> zoffset;
                }
            }
            AperatureGrid aGrid(nx, ny, geo, radius, xoffset, yoffset,zoffset);
            aperatureGridList.push_back(aGrid);
        }
        }
    }
           
}

void AperatureList::printApList(){
    for(AperatureGrid& aGrid: aperatureGridList){
        for(const std::pair<double,double>& coords: aGrid.get_aperatureGridCenters()){
            std::cout << coords.first << " " << coords.second << std::endl;
        }
    }

}

std::vector<AperatureGrid> AperatureList::get_aperatureGridList(){
    return aperatureGridList;
}
