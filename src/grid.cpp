#include "../include/grid.hpp"
#include <iostream>
#include <string>
#include <fstream>
#include <cmath>
using namespace std;
Grid::Grid(){
    ifstream grid_in("/Users/matt/Library/Mobile Documents/com~apple~CloudDocs/Documents/research/CXRIS/inputs/grid_input.txt");
    
    string testString;

    nr = 0;
   
    double fixedEdens = 0;
    double fixedIdens = 0;
    double fixedEtemp = 0;
    double fixedItemp = 0;
    int refineParam = 0;

    while (grid_in >> testString){

       if (testString == "GRID"){
        

            while(grid_in >> testString){
                if (testString == "END"){
                    break;
                }
                if (testString == "nr"){
                    grid_in >> nr;
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
        //TODO: write linking front and back of bounding sphere algorithm
        for(int i = 0; i < nr; i++){
            if(i == 0 && nr > 1){
                boundingSphere[i]->set_outerNeighbor(boundingSphere[i+1]);
            } else if (i == nr-1 && nr > 1){
                boundingSphere[i]->set_innerNeighbor(boundingSphere[i-1])
            }
            else{
                boundingSphere[i]->set_outerNeighbor(boundingSphere[i+1]);
                boundingSphere[i]->set_innerNeighbor(boundingSphere[i-1]);
            }
        }
        //printCoordsOfCells(refineParam);

    }
}

double Grid::get_maxRadius(){
    return maxRadiusCm;
}

std::vector<BoundingShellCollection*> Grid::get_boundingSphere(){
    return boundingSphere;
}

void Grid::printCoordsOfCells(int levelDes){
    for(BoundingShellCollection* bs: boundingSphere){
        bs->print_memberCoords(levelDes);
    }
}