#include "BoundingShell.hpp"
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
    if(innerR < std::numeric_limits< double >::min()){
       
    }
    dtheta = M_PI_2/(pow(2,level));
    dphi = M_PI_2/(pow(2,level));
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

    }


    

   


    plusPhi = new BoundPlane();
    minusPhi = new BoundPlane();
    plusTheta = new BoundPlane();
    minusTheta = new BoundPlane();
    
   
}

void BoundingShell::set_exitInterior(BoundingShell* bs){
    exitInterior = bs;
}
void BoundingShell::set_exitExterior(BoundingShell* bs){
    exitInterior = bs;
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