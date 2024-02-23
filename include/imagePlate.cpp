#include "imagePlate.hpp"
#include <fstream>
#include <string>
#include <utility>
#include <iostream>

using namespace std;

ImagePlate::ImagePlate(int nxi, int nyi, int IPIDi, double beginEi, double endEi, int nEi, double extXi, double extYi, double standOffi):
beginE(beginEi),
endE(endEi),
standOff(standOffi),
nE(nEi),
nx(nxi),
ny(nyi),
extX(extXi),
extY(extYi),
IPID(IPIDi)
{
    std::vector<double> temp(nx * ny,0.0);
    PSL = temp;
    double binWidthX = extX/(double) nx;
    double binWidthY = extY/(double) ny;
    for(int i = 0; i < nx; i++){
        for(int j = 0; j < ny; j++){
            IPPixelCoords.push_back(std::pair<double,double>(-extX/2.0 + binWidthX * (double) i + binWidthX/2.0,-extY/2.0+binWidthY * (double) j + binWidthY/2.0));
        }
    }     
}

void MakeStack(std::vector<ImagePlate*>& ipStack, int camID){
    ifstream imagePlate_in("/Users/matt/Library/Mobile Documents/com~apple~CloudDocs/Documents/research/CXRIS/inputs/imagePlate_input.txt");
    
    string testString;
    int testCID;

    while (imagePlate_in >> testString){

       if (testString == "IMAGEPLATE"){
        imagePlate_in >> testCID; 
        if(testCID == camID){
        
            int nx = 10;
            int ny = 10;
            int IPID = 0;
            double beginE = 0;
            double endE = 1;
            int nE = 2;
            double extX = 5;
            double extY = 5;
            double standOff = 10;

            while(imagePlate_in >> testString){
                if (testString == "END"){
                    break;
                }
                if (testString == "IPID"){
                    imagePlate_in >> IPID;
                }
                if (testString == "IPNX"){
                    imagePlate_in >> nx;
                }
                if (testString == "IPNY"){
                    imagePlate_in >> ny;
                }
                if (testString == "IPBEGINE"){
                    imagePlate_in >> beginE;
                }

                if (testString == "IPENDE"){
                    imagePlate_in >> endE;
                }
                
                if (testString == "IPEXTX"){
                    imagePlate_in >> extX;
                }
                
                if (testString == "IPEXTY"){
                    imagePlate_in >> extY;
                }

                if (testString == "IPSTANDOFF"){
                    imagePlate_in >> standOff;
                }
            }
            
        ImagePlate* ip = new ImagePlate(nx, ny, IPID, beginE, endE, nE, extX, extY, standOff);
        ipStack.push_back(ip);
            }
       }

    }
}
void ImagePlate::printCoordList(){
    for(int i = 0; i < nx; i++){
        for(int j = 0; j < ny; j++){
            std::cout << IPPixelCoords[i*ny + j].first << " "<< IPPixelCoords[i*ny + j].second << std::endl;
        }
    }
}

std::pair<double,double> ImagePlate::get_coords(int i, int j){
    return IPPixelCoords[i*ny + j];
}

int ImagePlate::get_nx(){
    return nx;
}

int ImagePlate::get_ny(){
    return ny;
}


double ImagePlate::get_standOff(){
    return standOff;
}

double ImagePlate::get_beginE(){
    return beginE;
}
double ImagePlate::get_endE(){
    return endE;
}

int ImagePlate::get_nE(){
    return nE;
}

void ImagePlate::write(int i, int j, Ray r){
    PSL[ny*i + j] = r.get_spectrum();
}

double ImagePlate::get_PSL(int i, int j){
    return PSL[ny*i + j];
}