#include "../include/pixel.hpp"
#include <vector>
#include <utility>

Pixel::Pixel(){
    coords = std::make_pair(0.0,0.0);

    childTopLeft = NULL;
    childTopRight = NULL;
    childBottomLeft = NULL;
    childBottomRight = NULL;

    neighborLeft = NULL;
    neighborRight = NULL;
    neighborTop = NULL;
    neighborBottom = NULL;
    neighborTopLeft = NULL;
    neighborTopRight = NULL;
    neighborBottomLeft = NULL;
    neighborBottomRight = NULL;


    level = 100;
    maxLevel = 0;
    refined = 0;
    traced  = 0;
    PSL = 0;
}

Pixel::Pixel(double xLoc, double yLoc, int leveli, double offsetX, double offsetY, int maxleveli):
childOffsetX(offsetX),
childOffsetY(offsetY),
maxLevel(maxleveli),
level(leveli)
{
    coords = std::make_pair(xLoc, yLoc);
    childTopLeft = NULL;
    childTopRight = NULL;
    childBottomLeft = NULL;
    childBottomRight = NULL;

    neighborLeft = NULL;
    neighborRight = NULL;
    neighborTop = NULL;
    neighborBottom = NULL;
    neighborTopLeft = NULL;
    neighborTopRight = NULL;
    neighborBottomLeft = NULL;
    neighborBottomRight = NULL;

    int refined = 0;
    PSL = 0;
    traced = 0;
}
std::vector<Pixel*> Pixel::refinePassive(){
    std::vector<Pixel*> newPixelsAndCoords;

    if(level==maxLevel || refined){
        return newPixelsAndCoords;
    }

    refined = 1;
    childTopLeft = new Pixel(coords.first - childOffsetX, coords.second + childOffsetY, level + 1, childOffsetX/4.0, childOffsetY/4.0, maxLevel);
    childTopRight = new Pixel(coords.first + childOffsetX, coords.second + childOffsetY, level+1, childOffsetX/4.0, childOffsetY/4.0, maxLevel);
    childBottomRight = new Pixel(coords.first + childOffsetX, coords.second - childOffsetY, level+1, childOffsetX/4.0, childOffsetY/4.0, maxLevel);
    childBottomLeft = new Pixel(coords.first - childOffsetX, coords.second - childOffsetY, level+ 1, childOffsetX/4.0, childOffsetY/4.0, maxLevel);

    newPixelsAndCoords.push_back(childBottomLeft);
    newPixelsAndCoords.push_back(childTopLeft);
    newPixelsAndCoords.push_back(childTopRight);
    newPixelsAndCoords.push_back(childBottomRight);
    setMyChildrensNeighbors();

    return newPixelsAndCoords;
}
void Pixel::setMyChildrensNeighbors(){
    
   
    childTopLeft->set_neighborRight(childTopRight);
    childTopLeft->set_neighborBottom(childBottomLeft);
    childTopLeft->set_neighborBottomRight(childBottomRight);
    
    

    childTopRight->set_neighborLeft(childTopLeft);
    childTopRight->set_neighborBottom(childBottomRight);
    childTopRight->set_neighborBottomLeft(childBottomLeft);

    childBottomRight->set_neighborTop(childTopRight);
    childBottomRight->set_neighborTopLeft(childTopLeft);
    childBottomRight->set_neighborLeft(childBottomLeft);

    childBottomLeft->set_neighborTop(childTopLeft);
    childBottomLeft->set_neighborRight(childBottomRight);
    childBottomLeft->set_neighborTopRight(childTopRight);

    if(neighborLeft){
        childTopLeft->set_neighborLeft(neighborLeft->get_childTopRight());
        childTopLeft->set_neighborBottomLeft(neighborLeft->get_childBottomRight());

        childBottomLeft->set_neighborLeft(neighborLeft->get_childBottomRight());
        childBottomLeft->set_neighborTopLeft(neighborLeft->get_childTopRight());

    }

    if(neighborTopLeft){
        childTopLeft->set_neighborTopLeft(neighborTopLeft->get_childBottomRight());
    }

    if(neighborTop){
        childTopLeft->set_neighborTop(neighborTop->get_childBottomLeft());
        childTopLeft->set_neighborTopRight(neighborTop->get_childBottomRight());

        childTopRight->set_neighborTop(neighborTop->get_childBottomRight());
        childTopRight->set_neighborTopLeft(neighborTop->get_childBottomLeft());

    }  

    if(neighborTopRight){
        childTopRight->set_neighborTopRight(neighborTopRight->get_childBottomLeft());
    }

    if(neighborRight){
        childTopRight->set_neighborRight(neighborRight->get_childTopLeft());
        childTopRight->set_neighborBottomRight(neighborRight->get_childBottomLeft());

        childBottomRight->set_neighborRight(neighborRight->get_childBottomLeft());
        childBottomRight->set_neighborTopRight(neighborRight->get_childTopLeft());

    }

    if(neighborBottomRight){
        childBottomRight->set_neighborBottomRight(neighborBottomRight->get_childTopLeft());
    }

    if(neighborBottom){
        childBottomRight->set_neighborBottom(neighborBottom->get_childTopRight());
        childBottomRight->set_neighborBottomLeft(neighborBottom->get_childTopLeft());

        childBottomLeft->set_neighborBottom(neighborBottom->get_childTopLeft());
        childBottomLeft->set_neighborBottomRight(neighborBottom->get_childTopRight());
    }

    if(neighborBottomLeft){
        childBottomLeft->set_neighborBottomLeft(neighborBottomLeft->get_childTopRight());
    }

}
std::vector<Pixel*> Pixel::refineActive(){
    std::vector<Pixel*> newPixelsAndCoords;
    if (level == maxLevel || refined){
        return newPixelsAndCoords;
    }
    refined = 1;
    childTopLeft = new Pixel(coords.first - childOffsetX, coords.second + childOffsetY, level + 1, childOffsetX/4.0, childOffsetY/4.0, maxLevel);
    childTopRight = new Pixel(coords.first + childOffsetX, coords.second + childOffsetY, level+1, childOffsetX/4.0, childOffsetY/4.0, maxLevel);
    childBottomRight = new Pixel(coords.first + childOffsetX, coords.second - childOffsetY, level+1, childOffsetX/4.0, childOffsetY/4.0, maxLevel);
    childBottomLeft = new Pixel(coords.first - childOffsetX, coords.second - childOffsetY, level+ 1, childOffsetX/4.0, childOffsetY/4.0, maxLevel);
    if(neighborLeft){
        auto newPixelsAndCoordsNeighbor = neighborLeft->refinePassive();
        newPixelsAndCoords.insert(newPixelsAndCoords.end(),newPixelsAndCoordsNeighbor.begin(),newPixelsAndCoordsNeighbor.end());
    }
    if(neighborRight){
        auto newPixelsAndCoordsNeighbor = neighborRight->refinePassive();
        newPixelsAndCoords.insert(newPixelsAndCoords.end(),newPixelsAndCoordsNeighbor.begin(),newPixelsAndCoordsNeighbor.end());
    }
    if(neighborTop){
        auto newPixelsAndCoordsNeighbor = neighborTop->refinePassive();
        newPixelsAndCoords.insert(newPixelsAndCoords.end(),newPixelsAndCoordsNeighbor.begin(),newPixelsAndCoordsNeighbor.end());
    }
       
    if(neighborBottom){
        auto newPixelsAndCoordsNeighbor = neighborBottom->refinePassive();
        newPixelsAndCoords.insert(newPixelsAndCoords.end(),newPixelsAndCoordsNeighbor.begin(),newPixelsAndCoordsNeighbor.end());
    }

    if(neighborTopLeft){
        auto newPixelsAndCoordsNeighbor = neighborTopLeft->refinePassive();
        newPixelsAndCoords.insert(newPixelsAndCoords.end(),newPixelsAndCoordsNeighbor.begin(),newPixelsAndCoordsNeighbor.end());
    }

    if(neighborTopRight){
        auto newPixelsAndCoordsNeighbor = neighborTopRight->refinePassive();
        newPixelsAndCoords.insert(newPixelsAndCoords.end(),newPixelsAndCoordsNeighbor.begin(),newPixelsAndCoordsNeighbor.end());
    }

    if(neighborBottomLeft){
        auto newPixelsAndCoordsNeighbor = neighborBottomLeft->refinePassive();
        newPixelsAndCoords.insert(newPixelsAndCoords.end(),newPixelsAndCoordsNeighbor.begin(),newPixelsAndCoordsNeighbor.end());
    }

    if(neighborBottomRight){
       auto newPixelsAndCoordsNeighbor = neighborBottomRight->refinePassive();
       newPixelsAndCoords.insert(newPixelsAndCoords.end(),newPixelsAndCoordsNeighbor.begin(),newPixelsAndCoordsNeighbor.end());
    }
    /*set neighbords for the top left child node of the active refine pixel*/
    setMyChildrensNeighbors();

   /* set the neighbors for the newly passively refined pixels*/
    /*if(neighborTopLeft){
        std::cout << "ntlo" << std::endl;
        neighborTopLeft->setMyChildrensNeighbors();
    }
    if(neighborTop){
        neighborTop->setMyChildrensNeighbors();
    }
    if(neighborTopRight){
        neighborTopRight->setMyChildrensNeighbors();
    }
    if(neighborRight){
        neighborRight->setMyChildrensNeighbors();
    }
    if(neighborBottomRight){
        neighborBottomRight->setMyChildrensNeighbors();
    }
    if(neighborBottom){
        neighborBottom->setMyChildrensNeighbors();
    }
    if(neighborBottomLeft){
        neighborBottomLeft->setMyChildrensNeighbors();
    }
    if(neighborLeft){
        neighborLeft->setMyChildrensNeighbors();
    }*/
    newPixelsAndCoords.push_back(childBottomLeft);
    newPixelsAndCoords.push_back(childTopLeft);
    newPixelsAndCoords.push_back(childTopRight);
    newPixelsAndCoords.push_back(childBottomRight);

    return newPixelsAndCoords;

}

std::vector<std::pair<Pixel*, std::pair<double,double> > > Pixel::traverse_coords(){
    std::vector<std::pair<Pixel*, std::pair<double, double > > > output;

    if(!refined){
        output.push_back(std::make_pair(this, coords));
    }
    else{
        return output = traverseCoordsHelper(this);
    }
    return output;
}


void Pixel::print_pixel(){
    if(!refined){
        std::cout << coords.first << " " << coords.second << " " << PSL <<std::endl;
    } else {
        childTopLeft->print_pixel();
        childTopRight->print_pixel();
        childBottomRight->print_pixel();
        childBottomLeft->print_pixel();
    }
}

void Pixel::add_PSL(Ray* r){
    PSL += r->get_spectrum();
}

int Pixel::get_refined(){
    return refined;
}

int Pixel::get_maxRefined(){
    return level == maxLevel;
}
//Getters and setters
//!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
std::pair<double,double> Pixel::get_coords(){
    return coords;
}
Pixel* Pixel::get_childBottomLeft(){
    return childBottomLeft;
}
Pixel* Pixel::get_childTopLeft(){
    return childTopLeft;
}
Pixel* Pixel::get_childBottomRight(){
    return childBottomRight;
}
Pixel* Pixel::get_childTopRight(){
    return childTopRight;
}

void Pixel::set_neighborBottom(Pixel* p){
    neighborBottom = p;
}
void Pixel::set_neighborTop(Pixel* p){
    neighborTop = p;
}

void Pixel::set_neighborLeft(Pixel* p){
    neighborTop = p;
}

void Pixel::set_neighborRight(Pixel* p){
    neighborRight = p;
}
void Pixel::set_neighborTopLeft(Pixel* p){
    neighborTopLeft = p;
}

void Pixel::set_neighborTopRight(Pixel* p){
    neighborTopRight = p;
}

void Pixel::set_neighborBottomRight(Pixel* p){
    neighborBottomRight = p;
}

void Pixel::set_neighborBottomLeft(Pixel* p){
    neighborBottomLeft = p;
}
//!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!

std::vector<std::pair<Pixel*, std::pair<double,double> > > traverseCoordsHelper(Pixel* p){
    std::vector<std::pair<Pixel*, std::pair<double, double > > > out;
    if(!p -> get_refined()){
        out.push_back(std::make_pair(p, p->get_coords()));
    } else{
        auto tchBottomL = traverseCoordsHelper(p->get_childBottomLeft());
        auto tchBottomR = traverseCoordsHelper(p->get_childBottomRight());
        auto tchTopR = traverseCoordsHelper(p->get_childTopRight());
        auto tchTopL = traverseCoordsHelper(p->get_childTopLeft());
        out.insert(out.end(),tchTopL.begin(),tchTopL.end());
        out.insert(out.end(), tchTopR.begin(), tchTopR.end());
        out.insert(out.end(), tchBottomR.begin(), tchBottomR.end());
        out.insert(out.end(), tchBottomL.begin(), tchBottomL.end());
    }
    return out;
}