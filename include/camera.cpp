#include "camera.hpp"
#include <fstream>
#include <string>
#include <utility>
#include <iostream>

using namespace std;
Camera::Camera(){
    ifstream camera_in("/Users/matt/Library/Mobile Documents/com~apple~CloudDocs/Documents/research/CXRIS/inputs/camera_input.txt");
    
    string testString;
    

    while (camera_in >> testString){

       if (testString == "CAMERA"){

        double camR = 10.0;
        double camTheta = 0.0;
        double camPhi = 0.0;

        cameraID = -1;
      

        while(camera_in >> testString){
            if (testString == "END"){
                break;
            }
            if (testString == "CameraR"){
                camera_in >> camR;
            }
            if (testString == "CameraTHETA"){
                camera_in >> camTheta;
            }
            if (testString == "CameraPHI"){
                camera_in >> camPhi;
            }
            if (testString == "CID"){
                camera_in >> cameraID;
            }
            
        }
        
        cameraPositionCart[0] = camR * sin(camTheta) * cos(camPhi);
        cameraPositionCart[1] = camR * sin(camTheta) * sin(camTheta);
        cameraPositionCart[2] = camR * cos(camTheta);

        xBasisVectorInImagePlane[0] = cos(camTheta)*cos(camPhi);
        xBasisVectorInImagePlane[1] = cos(camTheta)*sin(camPhi);
        xBasisVectorInImagePlane[2] = -sin(camTheta);

        yBasisVectorInImagePlane[0] = -sin(camPhi);
        yBasisVectorInImagePlane[1] = cos(camPhi);
        yBasisVectorInImagePlane[2] = 0.0;

        
        camUnitVec[0] = cameraPositionCart[0]/camR;
        camUnitVec[1] = cameraPositionCart[1]/camR;
        camUnitVec[2] = cameraPositionCart[2]/camR;

       }

    }


    cameraAperatureList.create(cameraID);
    MakeStack(IPStack, cameraID);

}

void Camera::outputFirstIPCoords(){
    IPStack[0]->printCoordList();
}

void Camera::beginRayTrace(Grid* hydroGrid){
    Ray xray;
    for(ImagePlate* IP: IPStack){
        int nx = IP->get_nx();
        int ny = IP->get_ny();
        auto IPstandOff = IP->get_standOff();
        auto beginE  = IP->get_beginE();
        auto endE = IP->get_endE();
        auto nE = IP->get_nE();
        for(auto pixelptr: IP->get_tree()){
            std::vector<std::pair<Pixel*, std::pair<double,double> > > PixelPtrcoordsList = pixelptr->traverse_coords();
            long int size = PixelPtrcoordsList.size();
            for(long int i = 0; i < size ; i++){
                int continueTracking = 1;
                auto IPcoord = PixelPtrcoordsList[i].second;
                Pixel* testPix = PixelPtrcoordsList[i].first;
                for(AperatureGrid apGrid: cameraAperatureList.get_aperatureGridList()){
                    if(!continueTracking){
                        break;
                    }
                    int gnx = apGrid.get_nx();
                    int gny = apGrid.get_ny();
                    
                    for(int gi = 0; gi < gnx && continueTracking; gi++){
                        for(int gj = 0; gj < gny && continueTracking; gj++){
                            auto apGridCoord = apGrid.get_coords(gi,gj);
                            auto apGridStandOff = apGrid.get_zoffset();
                            xray.updateRayDir(IPcoord, IPstandOff, apGridCoord, apGridStandOff, xBasisVectorInImagePlane, yBasisVectorInImagePlane, camUnitVec);
                            xray.updateRaySpec(nE);
                            std::pair<double*, int> initTrackCond = xray.launchRay(hydroGrid, beginE, endE, nE);
                            if(initTrackCond.second && !testPix->get_maxRefined()){
                                auto newpixelptrs = testPix->refineActive(); 
                                continueTracking = 0;
                                PixelPtrcoordsList.insert(PixelPtrcoordsList.begin() + i + 1, newpixelptrs.begin(),newpixelptrs.end());
                                size += newpixelptrs.size();
                                break;  
                            }
                            //Normally track ray through plasma. for now just add the value from launching
                            testPix->add_PSL((double) initTrackCond.second);
                        }
                    }
                }
            }
        }
    }
}

void Camera::outRayTrace(){
    for(ImagePlate* IP: IPStack){
        int nx = IP->get_nx();
        int ny = IP->get_ny();
        for(int i = 0; i < nx; i++){
            for(int j = 0; j < ny; j++){
                auto coord = IP->get_coords(i,j);
                auto PSL = IP->get_PSL(i,j);
                std::cout << coord.first << " " << coord.second << " " << PSL << std::endl;
            }
        }
    }
}