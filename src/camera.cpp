#include "../include/camera.hpp"
#include <fstream>
#include <string>
#include <utility>
#include <iostream>
#include <cstdlib>
#include <omp.h>

using namespace std;
Camera::Camera(){
    ifstream camera_in("../inputs/camera_input.txt");
    
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
    
    for(ImagePlate* IP: IPStack){
        auto IPstandOff = IP->get_standOff();
        auto beginE  = IP->get_beginE();
        auto endE = IP->get_endE();
        auto nE = IP->get_nE();
        std::vector<Pixel*> tree = IP->get_tree();
        std::vector<Pixel*> nextTree = tree;
        int nthreads = 1;
        omp_set_num_threads(nthreads);
        while(nextTree.size()){
            tree = nextTree;
            nextTree.erase(nextTree.begin(),nextTree.end());
            size_t initSize = tree.size();
            #pragma omp parallel for default(none) shared(tree, initSize, nE, beginE, endE,IPstandOff,hydroGrid, nthreads, nextTree) 
            for(size_t i = 0; i < initSize; i++){
                //std::cout << "Hello from thread:  " << omp_get_thread_num() << std::endl;
                std::vector<Pixel*> nextTreeLocal;
                Ray xray;
                Pixel* activePixel = tree[i]; 
                auto IPcoord = activePixel->get_coords();
                int continueTracking = 1;

                for(AperatureGrid apGrid: cameraAperatureList.get_aperatureGridList()){
                    if(!continueTracking){
                        break;
                    }
                    int gnx = apGrid.get_nx();
                    int gny = apGrid.get_ny();
                    
                    for(int gi = 0; gi < gnx; gi++){
                        for(int gj = 0; gj < gny; gj++){
                            auto apGridCoord = apGrid.get_coords(gi,gj);
                            auto apGridStandOff = apGrid.get_zoffset();
                            xray.updateRayDir(IPcoord, IPstandOff, apGridCoord, apGridStandOff, xBasisVectorInImagePlane, yBasisVectorInImagePlane, camUnitVec);
                            xray.updateRaySpec(nE);

                            std::pair<BoundingShellCollection*, std::vector<double> > initTrackCond = xray.launchRay(hydroGrid, beginE, endE, nE);
                            if(initTrackCond.second[0] && !activePixel->get_maxRefined()){
                                auto newpixelptrs = activePixel->refineActive();
                                nextTreeLocal.insert(nextTreeLocal.begin(), newpixelptrs.begin(),newpixelptrs.end());
                                
                            } else if(initTrackCond.second[0]){
                                xray.trackThroughGrid(initTrackCond.first,initTrackCond.second);
                                activePixel->add_PSL(&xray);
                            }
                            //Normally track ray through plasma. for now just add the value from launching
                            
                        }
                    }
                }
                #pragma omp critical
                {
                    nextTree.insert(nextTree.begin(), nextTreeLocal.begin(),nextTreeLocal.end());
                }  
            }
        }
    }
    
}

void Camera::outRayTrace(){
    for(ImagePlate* IP: IPStack){
        IP->dump_tree();
    }
}