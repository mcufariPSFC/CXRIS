#ifndef APERATURELIST_H
#define APERATURELIST_H

#include "aperatureGrid.hpp"
#include <vector>
class AperatureList{
public:
    AperatureList();

    void printApList();
    void create(int CID);
    std::vector<AperatureGrid> get_aperatureGridList();
private:
    std::vector<AperatureGrid> aperatureGridList;
    int nAps;

};
#endif 