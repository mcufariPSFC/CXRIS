#include "../include/boundingShellCollection.hpp"
#include <cmath>
double M_PI3_4 = 3.0 * M_PI_4;
BoundingShellCollection::BoundingShellCollection(double rin, double rout, int maxRefinei):
inR(rin),
outR(rout),
maxRefine(maxRefinei)
{
    firstOct = new BoundingShell(inR, outR, maxRefine, 0, M_PI_4, M_PI_4);
    secondOct = new BoundingShell(inR, outR, maxRefine, 0, M_PI_4, 3.0 * M_PI_4);
    thirdOct = new BoundingShell(inR, outR, maxRefine, 0, M_PI_4, 5.0 * M_PI_4);
    fourthOct = new BoundingShell(inR, outR, maxRefine, 0, M_PI_4, 7.0 * M_PI_4);


    fifthOct = new BoundingShell(inR, outR, maxRefine, 0, M_PI3_4, M_PI_4);
    sixthOct = new BoundingShell(inR, outR, maxRefine, 0, M_PI3_4, M_PI3_4);
    seventhOct = new BoundingShell(inR, outR, maxRefine, 0, M_PI3_4, 5.0 * M_PI_4);
    eighthOct = new BoundingShell(inR, outR, maxRefine, 0, M_PI3_4, 7.0 * M_PI_4);

    //need to link these somehow...
    //need to account for bounding plane when innerR  = 0
    

}

void BoundingShellCollection::set_innerNeighbor(BoundingShellCollection* bsc){
    //set inner neighbor for first octant
    if(firstOct){
        firstOct->set_exitInterior(bsc->get_firstOct());
    }
    if(secondOct){
        secondOct->set_exitInterior(bsc->get_secondOct());
    }
    if(thirdOct){
        thirdOct->set_exitInterior(bsc->get_thirdOct());
    }
    if(fourthOct){
        fourthOct->set_exitInterior(bsc->get_fourthOct());
    }
    if(fifthOct){
        fifthOct->set_exitInterior(bsc->get_fifthOct());
    }
    if(sixthOct){
        sixthOct->set_exitInterior(bsc->get_sixthOct());
    }
    if(seventhOct){
        seventhOct->set_exitInterior(bsc->get_seventhOct());
    }
    if(eighthOct){
        eighthOct->set_exitInterior(bsc->get_eighthOct());
    }
}


void BoundingShellCollection::set_outerNeighbor(BoundingShellCollection* bsc){
    //set inner neighbor for first octant
    if(firstOct){
        firstOct->set_exitExterior(bsc->get_firstOct());
    }
    if(secondOct){
        secondOct->set_exitExterior(bsc->get_secondOct());
    }
    if(thirdOct){
        thirdOct->set_exitExterior(bsc->get_thirdOct());
    }
    if(fourthOct){
        fourthOct->set_exitExterior(bsc->get_fourthOct());
    }
    if(fifthOct){
        fifthOct->set_exitExterior(bsc->get_fifthOct());
    }
    if(sixthOct){
        sixthOct->set_exitExterior(bsc->get_sixthOct());
    }
    if(seventhOct){
        seventhOct->set_exitExterior(bsc->get_seventhOct());
    }
    if(eighthOct){
        eighthOct->set_exitExterior(bsc->get_eighthOct());
    }
}

BoundingShell* BoundingShellCollection::get_firstOct(){
    return firstOct;
}

BoundingShell* BoundingShellCollection::get_secondOct(){
    return secondOct;
}

BoundingShell* BoundingShellCollection::get_thirdOct(){
    return thirdOct;
}
BoundingShell* BoundingShellCollection::get_fourthOct(){
    return fourthOct;
}

BoundingShell* BoundingShellCollection::get_fifthOct(){
    return fifthOct;
}

BoundingShell* BoundingShellCollection::get_sixthOct(){
    return sixthOct;
}

BoundingShell* BoundingShellCollection::get_seventhOct(){
    return seventhOct;
}

BoundingShell* BoundingShellCollection::get_eighthOct(){
    return eighthOct;
}

void BoundingShellCollection::print_memberCoords(int levelDes){
    firstOct->print_memberCoords(levelDes);
    secondOct->print_memberCoords(levelDes);
    thirdOct->print_memberCoords(levelDes);
    fourthOct->print_memberCoords(levelDes);
    fifthOct->print_memberCoords(levelDes);
    sixthOct->print_memberCoords(levelDes);
    seventhOct->print_memberCoords(levelDes);
    eighthOct->print_memberCoords(levelDes);
}

double BoundingShellCollection::get_outR(){
    return outR;
}



void BoundingShellCollection::propagateHit(Ray* r, std::vector<double> intersectionPt){
    
    
    if(intersectionPt[0] > 0 && intersectionPt[1] >= 0 && intersectionPt[2] >= 0 && firstOct){
        firstOct->propagateHit(r, intersectionPt);
    }
    else if(intersectionPt[0] > 0 && intersectionPt[1] <= 0 && intersectionPt[2] >= 0 && secondOct){
        secondOct->propagateHit(r, intersectionPt);
    }
    else if(intersectionPt[0] < 0 && intersectionPt[1] <= 0 && intersectionPt[2] >= 0 && thirdOct){
        thirdOct->propagateHit(r, intersectionPt);
    }
    else if(intersectionPt[0] > 0 && intersectionPt[1] <= 0 && intersectionPt[2] >= 0 && fourthOct){
        fourthOct->propagateHit(r, intersectionPt);
    }


    else if(intersectionPt[0] >= 0 && intersectionPt[1] > 0 && intersectionPt[2] < 0 && fifthOct){
        fifthOct->propagateHit(r, intersectionPt);
    }
    else if(intersectionPt[0] >= 0 && intersectionPt[1] < 0 && intersectionPt[2] < 0 && sixthOct){
        sixthOct->propagateHit(r, intersectionPt);
    }
    else if(intersectionPt[0] <= 0 && intersectionPt[1] < 0 && intersectionPt[2] < 0 && seventhOct){
        seventhOct->propagateHit(r, intersectionPt);
    }
    else if(intersectionPt[0] >= 0 && intersectionPt[1] < 0 && intersectionPt[2] < 0 && eighthOct){
        eighthOct->propagateHit(r, intersectionPt);
    }
    
}