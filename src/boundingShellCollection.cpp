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
    eightOct = new BoundingShell(inR, outR, maxRefine, 0, M_PI3_4, 7.0 * M_PI_4);

    //need to link these somehow...
    //need to account for bounding plane when innerR  = 0
    

}

void BoundingShellCollection::print_memberCoords(int levelDes){
    firstOct->print_memberCoords(levelDes);
    secondOct->print_memberCoords(levelDes);
    thirdOct->print_memberCoords(levelDes);
    fourthOct->print_memberCoords(levelDes);
    fifthOct->print_memberCoords(levelDes);
    sixthOct->print_memberCoords(levelDes);
    seventhOct->print_memberCoords(levelDes);
    eightOct->print_memberCoords(levelDes);
}

double BoundingShellCollection::get_outR(){
    return outR;
}