#include "../include/boundingShell.hpp"
#include "../include/ray.hpp"
#include <limits>
#include <cmath>
#include <iostream>

BoundingShell::BoundingShell(double inny, double outy, int maxRefine, int curLevel,double ctheta, double cphi):
level(curLevel),
maxRefine(maxRefine),
innerR(inny),
outerR(outy),
centerPhi(cphi),
centerTheta(ctheta)
{
    dtheta = M_PI_2/(pow(2,level));
    dphi = M_PI_2/(pow(2,level));
    
    if(innerR < std::numeric_limits< double >::min()){
       
    }
   
    if(level < maxRefine){
    uthetauphi = new BoundingShell(innerR, outerR, maxRefine, level+1, centerTheta + dtheta/4.0, centerPhi + dphi/4.0);
    uthetalphi = new BoundingShell(innerR, outerR, maxRefine, level+1, centerTheta + dtheta/4.0, centerPhi - dphi/4.0);
    lthetauphi = new BoundingShell(innerR, outerR, maxRefine, level+1, centerTheta - dtheta/4.0, centerPhi + dphi/4.0);
    lthetalphi = new BoundingShell(innerR, outerR, maxRefine, level+1, centerTheta - dtheta/4.0, centerPhi - dphi/4.0);
    
    /*Set exit pointers for each plane*/
    uthetauphi->set_exitMinusTheta(lthetauphi);
    uthetauphi->set_exitMinusPhi(uthetalphi);
    uthetauphi->set_exitPlusTheta(exitPlusTheta);
    uthetauphi->set_exitPlusPhi(exitPlusPhi);


    uthetalphi->set_exitMinusTheta(lthetalphi);
    uthetalphi->set_exitPlusPhi(uthetalphi);
    uthetalphi->set_exitPlusTheta(exitPlusTheta);
    uthetalphi->set_exitMinusPhi(exitMinusPhi);

    lthetauphi->set_exitPlusTheta(uthetauphi);
    lthetauphi->set_exitMinusPhi(lthetalphi);
    lthetauphi->set_exitMinusTheta(exitMinusTheta);
    lthetauphi->set_exitPlusPhi(exitPlusPhi);

    lthetalphi->set_exitPlusTheta(uthetalphi);
    lthetalphi->set_exitPlusPhi(lthetauphi);
    lthetalphi->set_exitMinusPhi(exitMinusPhi);
    lthetalphi->set_exitMinusTheta(exitMinusTheta);

    double* verts;
    verts = (double*) malloc(3 * sizeof(double) * 8);
    
    verts[0] = innerR * sin(ctheta+dtheta/2.0)*cos(cphi+dphi/2.0);  // inner up right
    verts[1] = innerR * sin(ctheta+dtheta/2.0) * sin(cphi + dphi/2.0);
    verts[2] = innerR * cos(ctheta+dtheta/2.0);

    verts[3] = innerR * sin(ctheta+dtheta/2.0)*cos(cphi-dphi/2.0);  // inner up left  
    verts[4] = innerR * sin(ctheta+dtheta/2.0) * sin(cphi - dphi/2.0);
    verts[5] = innerR * cos(ctheta+dtheta/2.0);

    verts[6] = innerR * sin(ctheta-dtheta/2.0)*cos(cphi-dphi/2.0);  //inner  down left
    verts[7] = innerR * sin(ctheta-dtheta/2.0) * sin(cphi - dphi/2.0);
    verts[8] = innerR * cos(ctheta-dtheta/2.0);

    verts[9] = innerR * sin(ctheta-dtheta/2.0)*cos(cphi+dphi/2.0);  // inner down right 
    verts[10] = innerR * sin(ctheta-dtheta/2.0) * sin(cphi + dphi/2.0);
    verts[11] = innerR * cos(ctheta-dtheta/2.0);

    verts[12] = outerR * sin(ctheta+dtheta/2.0)*cos(cphi+dphi/2.0);  // outerR up right
    verts[13] = outerR * sin(ctheta+dtheta/2.0) * sin(cphi + dphi/2.0);
    verts[14] = outerR * cos(ctheta+dtheta/2.0);

    verts[15] = outerR * sin(ctheta+dtheta/2.0)*cos(cphi-dphi/2.0);  // outerR up left  
    verts[16] = outerR * sin(ctheta+dtheta/2.0) * sin(cphi - dphi/2.0);
    verts[17] = outerR * cos(ctheta+dtheta/2.0);

    verts[18] = outerR * sin(ctheta-dtheta/2.0)*cos(cphi-dphi/2.0);  //outerR  down left
    verts[19] = outerR * sin(ctheta-dtheta/2.0) * sin(cphi - dphi/2.0);
    verts[20] = outerR * cos(ctheta-dtheta/2.0);

    verts[21] = outerR * sin(ctheta-dtheta/2.0)*cos(cphi+dphi/2.0);  // outerR down right 
    verts[22] = outerR * sin(ctheta-dtheta/2.0) * sin(cphi + dphi/2.0);
    verts[23] = outerR * cos(ctheta-dtheta/2.0);

    /* Creating plane structures bounding this volume*/
    plusPhiPlane = new BoundPlane(&verts[0], &verts[12],&verts[21],&verts[9]);
    minusPhiPlane = new BoundPlane(&verts[3],&verts[15],&verts[18],&verts[6]);
    plusThetaPlane = new BoundPlane(&verts[6],&verts[9],&verts[21],&verts[18]);
    minusThetaPlane = new BoundPlane(&verts[0],&verts[12],&verts[15],&verts[3]);

    }


       
}

void BoundingShell::set_exitInterior(BoundingShell* bs){
    exitInterior = bs;
    if(uthetauphi){
        uthetauphi->set_exitInterior(bs);
    }
    if(uthetalphi){
        uthetalphi->set_exitInterior(bs);
    }
    if(lthetauphi){
        lthetauphi->set_exitInterior(bs);
    }    
    if(lthetalphi){  
        lthetalphi->set_exitInterior(bs);
    }
}
void BoundingShell::set_exitExterior(BoundingShell* bs){
    exitInterior = bs;
    if(uthetauphi){
        uthetauphi->set_exitExterior(bs);
    }
    if(uthetalphi){
        uthetalphi->set_exitExterior(bs);
    }
    if(lthetauphi){
        lthetauphi->set_exitExterior(bs);
    }    
    if(lthetalphi){  
        lthetalphi->set_exitExterior(bs);
    }
}



void BoundingShell::set_exitPlusTheta(BoundingShell* bs){
    exitPlusTheta = bs;
}
void BoundingShell::set_exitMinusTheta(BoundingShell* bs){
    exitMinusTheta = bs;
}
void BoundingShell::set_exitMinusPhi(BoundingShell* bs){
    exitMinusPhi = bs;
}
void BoundingShell::set_exitPlusPhi(BoundingShell* bs){
    exitPlusPhi = bs;
}

void BoundingShell::print_memberCoords(int levelDes){
    if(level != levelDes){
        if(uthetauphi){
            uthetauphi->print_memberCoords(levelDes);
        }
        if(uthetalphi){
            uthetalphi->print_memberCoords(levelDes);
        }
        if(lthetalphi){
            lthetalphi->print_memberCoords(levelDes);
        }
        if(lthetauphi){
            lthetauphi->print_memberCoords(levelDes);
        }
    } else {
        //inR + dtheta + dphi
        std::cout << innerR * sin(centerTheta+dtheta/2.0)*cos(centerPhi+dphi/2.0) << " ";
        std::cout << innerR * sin(centerTheta+dtheta/2.0) * sin(centerPhi+dphi/2.0) << " ";
        std::cout << innerR * cos(centerTheta+dtheta/2.0)<< " ";

        //inR - dtheta + dphi
        std::cout << innerR * sin(centerTheta-dtheta/2.0)*cos(centerPhi+dphi/2.0) << " ";
        std::cout << innerR * sin(centerTheta-dtheta/2.0) * sin(centerPhi+dphi/2.0) << " ";
        std::cout << innerR * cos(centerTheta-dtheta/2.0)<< " ";

        //inR + dtheta - dphi
        std::cout << innerR * sin(centerTheta+dtheta/2.0)*cos(centerPhi-dphi/2.0) << " ";
        std::cout << innerR * sin(centerTheta+dtheta/2.0) * sin(centerPhi-dphi/2.0) << " ";
        std::cout << innerR * cos(centerTheta+dtheta/2.0) << " ";
        //inR - dtheta - dphi
        std::cout << innerR * sin(centerTheta-dtheta/2.0)*cos(centerPhi-dphi/2.0) << " ";
        std::cout << innerR * sin(centerTheta-dtheta/2.0) * sin(centerPhi-dphi/2.0) << " ";
        std::cout << innerR * cos(centerTheta-dtheta/2.0) << " ";

        //outR + dtheta + dphi
        std::cout << outerR * sin(centerTheta+dtheta/2.0)*cos(centerPhi+dphi/2.0) << " ";
        std::cout << outerR * sin(centerTheta+dtheta/2.0) * sin(centerPhi+dphi/2.0) << " ";
        std::cout << outerR * cos(centerTheta+dtheta/2.0) << " ";

        //outR - dtheta + dphi
        std::cout << outerR * sin(centerTheta-dtheta/2.0)*cos(centerPhi+dphi/2.0) << " ";
        std::cout << outerR * sin(centerTheta-dtheta/2.0) * sin(centerPhi+dphi/2.0) << " ";
        std::cout << outerR * cos(centerTheta-dtheta/2.0) << " ";

        //outR + dtheta - dphi
        std::cout << outerR * sin(centerTheta+dtheta/2.0)*cos(centerPhi-dphi/2.0) << " ";
        std::cout << outerR * sin(centerTheta+dtheta/2.0) * sin(centerPhi-dphi/2.0) << " ";
        std::cout << outerR * cos(centerTheta+dtheta/2.0) << " ";
        //outR - dtheta - dphi
        std::cout << outerR * sin(centerTheta-dtheta/2.0)*cos(centerPhi-dphi/2.0) << " ";
        std::cout << outerR * sin(centerTheta-dtheta/2.0) * sin(centerPhi-dphi/2.0) << " ";
        std::cout << outerR * cos(centerTheta-dtheta/2.0) << std::endl;

    }
}

double sgn(double val) {
    return (0.0 < val) - (val < 0.0);
}

std::vector<double> ArrayToVector(double* arr, size_t arr_len) {
    return std::vector<double>(arr, arr + arr_len);
}

void BoundingShell::propagateHit(Ray* r, std::vector<double> intersectionPt){
    if(uthetauphi){
        double rad = sqrt(intersectionPt[0]*intersectionPt[0] + intersectionPt[1]*intersectionPt[1]+intersectionPt[2]*intersectionPt[2]);
        double theta = acos(intersectionPt[2]/rad);
        double phi = sgn(intersectionPt[1])*acos(intersectionPt[0]/sqrt(intersectionPt[0]*intersectionPt[0]+intersectionPt[1]*intersectionPt[1]));
        double thetaDif = theta - centerTheta;
        double phiDif = phi - centerPhi ;
        if(phiDif > 0){
            if(thetaDif > 0){
                uthetauphi->propagateHit(r, intersectionPt);
            }
            else{
                lthetauphi->propagateHit(r, intersectionPt);
            }
        }
        else{
            if(thetaDif > 0){
                uthetalphi->propagateHit(r, intersectionPt);
            }
            else{
                lthetalphi->propagateHit(r,intersectionPt);
            }
        }
        
    } else {

        r->addPayload(1.0);
        double* dir  = r->get_direction();
        double* movedRay;
        movedRay = (double*) malloc(3 * sizeof(double));

        movedRay[0] = dir[0]*1e-6 + intersectionPt[0];
        movedRay[1] = dir[1]*1e-6 + intersectionPt[1];
        movedRay[2] = dir[2]*1e-6 + intersectionPt[2];

        //compute intersection table for each group of vertices
        if(double* intPt = testInnerShellIntersection(movedRay, dir)){
            if(exitInterior){
                exitInterior->propagateHit(r, ArrayToVector(intPt,3));
            } else {
                std::cout << "Error! Inner intersection with nonexistent shell" << std::endl;
                std::cout << "Shell R in: " << innerR << "\t shell R out: " << outerR <<  std::endl;
                exit(1); 
            }
        }
        if(double* intPt = plusPhiPlane->testIntersection(movedRay, dir)){
            if(exitPlusPhi){
                exitPlusPhi->propagateHit(r, ArrayToVector(intPt,3));
            } else {
                std::cout << "Error!";
            }
        } else if(double* intPt = minusPhiPlane->testIntersection(movedRay, dir)){
            if(exitMinusPhi){
                exitMinusPhi->propagateHit(r, ArrayToVector(intPt,3));
            } else{
                return;
            }
        } else if (double* intPt = plusThetaPlane->testIntersection(movedRay, dir)){
            if(exitPlusTheta){
                exitPlusTheta->propagateHit(r,ArrayToVector(intPt,3));
            }
        } else if(double* intPt = minusThetaPlane->testIntersection(movedRay, dir)){
            if(exitMinusTheta){
                exitMinusTheta->propagateHit(r, ArrayToVector(intPt,3));
            }
        } else if (double* intPt = testOuterShellIntersection(movedRay, dir)) {
            if(exitExterior){
                exitExterior->propagateHit(r, ArrayToVector(intPt,3));
            } else {
                return;
            }
        } else {
            //std::cout << "No intersections!!" << "\t exiting" << std::endl;
            //exit(1);
        }
    
    }

}

double* BoundingShell::testInnerShellIntersection(double* origin, double* dir){
    return 0;
}
double* BoundingShell::testOuterShellIntersection(double* origin, double* dir){
    return 0;
}