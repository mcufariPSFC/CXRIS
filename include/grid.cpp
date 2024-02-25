#include "grid.hpp"
#include <iostream>
#include <string>
#include <fstream>
#include <cmath>
using namespace std;
Grid::Grid(){
    ifstream grid_in("/Users/matt/Library/Mobile Documents/com~apple~CloudDocs/Documents/research/CXRIS/inputs/grid_input.txt");
    
    string testString;

    nr = 0;
    ntheta = 1;
    nphi = 1;
    double fixedEdens = 0;
    double fixedIdens = 0;
    double fixedEtemp = 0;
    double fixedItemp = 0;
    int refineParam = 1;
    while (grid_in >> testString){

       if (testString == "GRID"){
        

            while(grid_in >> testString){
                if (testString == "END"){
                    break;
                }
                if (testString == "nr"){
                    grid_in >> nr;
                }
                if (testString == "nth"){
                    grid_in >> ntheta;
                }
                if (testString == "nphi"){
                    grid_in >> nphi;
                }
                if (testString == "edens"){
                    grid_in >> fixedEdens;
                }

                if (testString == "idens"){
                    grid_in >> fixedIdens;
                }
                
                if (testString == "maxR"){
                    grid_in >> maxRadiusCm;
                }

                if(testString == "itemp"){
                    grid_in >> fixedItemp;
                }

                if(testString == "etemp"){
                    grid_in >> fixedEtemp;
                }
                
                if(testString == "refinement"){
                    grid_in >> refineParam;
                }
            
            }

       }

        std::vector<double> tmpTE(nr*ntheta*nphi, fixedEtemp);
        electronTemp = tmpTE;
        std::vector<double> tmpTi(nr*ntheta*nphi, fixedItemp);
        ionTemp = tmpTi;
        std::vector<double> tmpID(nr*ntheta*nphi, fixedIdens);
        ionDensity = tmpID;
        std::vector<double> tmpED(nr*ntheta*nphi, fixedEdens);
        electronDensity = tmpED;

        for (int i = 0; i < nr; i++){
             BoundingShellCollection* newShell = new BoundingShellCollection(maxRadiusCm / nr * i,maxRadiusCm/nr * (i+1),refineParam);
             boundingSphere.push_back(newShell);
        }
       
        printCoordsOfCells(refineParam);

    }
}

double Grid::get_maxRadius(){
    return maxRadiusCm;
}

void Grid::printCoordsOfCells(int levelDes){
    for(BoundingShellCollection* bs: boundingSphere){
        bs->print_memberCoords(levelDes);
    }
}