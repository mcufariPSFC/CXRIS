#include "../include/pixel.hpp"
#include <vector>
#include <utility>

Pixel::Pixel(){
    coords = std::make_pair(0.0,0.0);

    childTopLeft = NULL;
    childTopRight = NULL;
    childBottomLeft = NULL;
    childBottomRight = NULL;

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
    childLeft = NULL;
    childRight = NULL;
    childTop = NULL;
    childBottom = NULL;

    if(level >= maxLevel){
        refined = 1;
    }
    PSL = 0;
    traced = 0;
}

std::vector<Pixel*> Pixel::refineActive(){
    std::vector<Pixel*> newPixelsAndCoords;
    if (refined){
        std::cout << "should not have got here" << std::endl;
        return newPixelsAndCoords;
    }
    
    childTopLeft = new Pixel(coords.first - 1.5 * childOffsetX, coords.second + 1.5 * childOffsetY, level + 1, childOffsetX/2.0, childOffsetY/2.0, maxLevel);
    childTopRight = new Pixel(coords.first + 1.5 * childOffsetX, coords.second + 1.5 * childOffsetY, level+1, childOffsetX/2.0, childOffsetY/2.0, maxLevel);
    childBottomRight = new Pixel(coords.first + 1.5 * childOffsetX, coords.second - 1.5 * childOffsetY, level+1, childOffsetX/2.0, childOffsetY/2.0, maxLevel);
    childBottomLeft = new Pixel(coords.first - 1.5 * childOffsetX, coords.second - 1.5 * childOffsetY, level+ 1, childOffsetX/2.0, childOffsetY/2.0, maxLevel);
    childTop = new Pixel(coords.first , coords.second + 1.5 * childOffsetY, level+ 1, childOffsetX/2.0, childOffsetY/2.0, maxLevel);
    childBottom = new Pixel(coords.first , coords.second - 1.5 * childOffsetY, level+ 1, childOffsetX/2.0, childOffsetY/2.0, maxLevel);
    childLeft = new Pixel(coords.first - 1.5 * childOffsetX, coords.second, level+ 1, childOffsetX/2.0, childOffsetY/2.0, maxLevel);
    childRight = new Pixel(coords.first + 1.5 *  childOffsetX, coords.second, level+ 1, childOffsetX/2.0, childOffsetY/2.0, maxLevel);
    
    childOffsetX = childOffsetX/2.0;
    childOffsetY = childOffsetY/2.0;
    level += 1;
    if(level >= maxLevel){
        refined = 1;
    }
    
    newPixelsAndCoords.push_back(childBottomLeft);
    newPixelsAndCoords.push_back(childTopLeft);
    newPixelsAndCoords.push_back(childTopRight);
    newPixelsAndCoords.push_back(childBottomRight);
    newPixelsAndCoords.push_back(childTop);
    newPixelsAndCoords.push_back(childLeft);
    newPixelsAndCoords.push_back(childRight);
    newPixelsAndCoords.push_back(childBottom);

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
    std::cout << coords.first << " " << coords.second << " " << PSL <<std::endl;
    if(childTopLeft) {
        childTopLeft->print_pixel();
        childTopRight->print_pixel();
        childBottomRight->print_pixel();
        childBottomLeft->print_pixel();
        childTop->print_pixel();
        childBottom->print_pixel();
        childRight->print_pixel();
        childLeft->print_pixel();
    }
}

void Pixel::add_PSL(Ray* r){
    PSL += r->get_spectrum();
}

int Pixel::get_refined(){
    return refined;
}

int Pixel::get_maxRefined(){
    return refined;
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

Pixel* Pixel::get_childBottom(){
    return childBottom;
}

Pixel* Pixel::get_childTop(){
    return childTop;
}
Pixel* Pixel::get_childLeft(){
    return childLeft;
}
Pixel* Pixel::get_childRight(){
    return childRight;
}
//!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!

std::vector<std::pair<Pixel*, std::pair<double,double> > > traverseCoordsHelper(Pixel* p){
    std::vector<std::pair<Pixel*, std::pair<double, double > > > out;
    if(!p -> get_refined()){
        out.push_back(std::make_pair(p, p->get_coords()));
    } else{
        auto tchBottomL = traverseCoordsHelper(p->get_childBottomLeft());
        auto tchBottom = traverseCoordsHelper(p->get_childBottom());
        auto tchBottomR = traverseCoordsHelper(p->get_childBottomRight());
        auto tchLeft = traverseCoordsHelper(p->get_childLeft());
        auto tchTopR = traverseCoordsHelper(p->get_childTopRight());
        auto tchTopL = traverseCoordsHelper(p->get_childTopLeft());
        auto tchR = traverseCoordsHelper(p->get_childRight());
        auto tchTop = traverseCoordsHelper(p->get_childTop());

        out.insert(out.end(),tchTopL.begin(),tchTopL.end());
        out.insert(out.end(), tchTopR.begin(), tchTopR.end());
        out.insert(out.end(), tchBottomR.begin(), tchBottomR.end());
        out.insert(out.end(), tchBottomL.begin(), tchBottomL.end());
        out.insert(out.end(),tchBottom.begin(),tchBottom.end());
        out.insert(out.end(),tchLeft.begin(),tchLeft.end());
        out.insert(out.end(),tchTop.begin(),tchTop.end());
        out.insert(out.end(),tchR.begin(),tchR.end());

    }
    return out;
}


