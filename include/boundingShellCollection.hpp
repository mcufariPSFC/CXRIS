#ifndef BOUNDINGSHELLCOLLECTION_H
#define BOUNDINGSHELLCOLLECTION_H
#include "boundingShell.hpp"


class BoundingShellCollection{
public:
    
    BoundingShellCollection(double rin, double rout, int maxRefine);
    void print_memberCoords(int levelDes);
    double get_outR();
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
    BoundingShell* eightOct;
};

#endif