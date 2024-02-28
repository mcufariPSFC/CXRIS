#ifndef BOUNDINGSHELLCOLLECTION_H
#define BOUNDINGSHELLCOLLECTION_H
#include "boundingShell.hpp"


class BoundingShellCollection{
public:
    
    BoundingShellCollection(double rin, double rout, int maxRefine);
    void print_memberCoords(int levelDes);
    double get_outR();
    
    void set_innerNeighbor(BoundingShellCollection* bsc);
    void set_outerNeighbor(BoundingShellCollection* bsc);

    BoundingShell* get_firstOct();
    BoundingShell* get_secondOct();
    BoundingShell* get_thirdOct();
    BoundingShell* get_fourthOct();
    BoundingShell* get_fifthOct();
    BoundingShell* get_sixthOct();
    BoundingShell* get_seventhOct();
    BoundingShell* get_eighthOct();

    void propagateHit(Ray* r, std::vector<double> intersectionPt);

private:
    double inR;
    double outR;
    int maxRefine;

    BoundingShell* firstOct;
    BoundingShell* secondOct;
    BoundingShell* thirdOct;
    BoundingShell* fourthOct;
    BoundingShell* fifthOct;
    BoundingShell* sixthOct;
    BoundingShell* seventhOct;
    BoundingShell* eighthOct;
};

#endif