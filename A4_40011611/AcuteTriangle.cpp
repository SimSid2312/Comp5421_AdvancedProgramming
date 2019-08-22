#include <cmath>
#include "AcuteTriangle.h"
using std::vector;
/**
	Assignment 4, AcuteTriangle.cpp
	Purpose: Class AcuteTriangle(Concrete Class) is derived class of class Triangle
             AcuteTriangle.cpp is implementation of AcuteTriangle.h headerfile
	@author Simran Sidhu
*/

/*
Paramterized ctor to initiate an Acute Triangle object and it calls the base class(Triangle) ctor passing in the name and description
@ b1 constant reference to a double holding the width of bounding box
@ name const reference to a string holding name of the shape object
@ description const reference to a string holding description of the shape object
*/
AcuteTriangle::AcuteTriangle(const double &b1 ,
                      const string &name,
                    const string &description) : b(std::fmod(b1,2)==0 ? b1+1:b1),
                                                                    Triangle(name,description){};

/*
Computes geometric area
@return (double) geometric area of the shape object - Acute Triangle
*/
double AcuteTriangle::computeGeometricArea() const{
    double geometricArea=( ((this->b+1)/2) * this->b )/2;
    return this->roundOff(geometricArea);
}

/*
Computes geometric perimeter
@return (double) geometric perimeter of the shape object - Acute Triangle
*/
double AcuteTriangle::computeGeometricPerimeter() const{
    double geometricPerimeter= this->b+ (2*sqrt( (0.25*this->b*this->b)+ ( ((this->b+1)/2) * ((this->b+1)/2) ) ));
    return this->roundOff(geometricPerimeter);
}
/*
Computes screen area
@return (int) screen area of the shape object - Acute Triangle
*/
int AcuteTriangle::computeScreenArea() const{
    int screenArea=((this->b+1)/2)*((this->b+1)/2);
    return screenArea;
}
/*
Computes screen perimeter
@return (int) screen perimeter of the shape object - Acute Triangle
*/
int AcuteTriangle::computeScreenPerimeter() const{
    int screenPerimeter=4*(((this->b+1)/2) -1);
    return screenPerimeter;
}
/*
Returns height of the bounding box
@return (int) height of the bounding box of the shape object - Acute Triangle
*/
int AcuteTriangle::getBoundingBoxHeight() const{
    return ((this->b+1)/2);
}

/*
Returns width of the bounding box
@return (int) width of the bounding box of the shape object - Acute Triangle
*/
int AcuteTriangle::getBoundingBoxWidth() const{
    return this->b;
}

/*
Draws a textual image for the shape object on a two dimensional grid and returns that grid
@return (vector<vector<char>>)  two dimensional grid of textual image for the shape object - Acute Triangle
*/
vector<vector<char>> AcuteTriangle::draw(char fChar,char bChar) const{
    vector<vector<char>>twoDimensionGrid;

    //Fill the 2d grid with bChar
    for(int i=0;i<this->getBoundingBoxHeight();i++){
        vector<char> gridRow;
        for(int j=0;j<this->getBoundingBoxWidth();j++){
            gridRow.push_back(bChar);
        }
        twoDimensionGrid.push_back(gridRow);
     }


     int upperLimit=getBoundingBoxWidth()-1; //Last row as the upper limit
     int lowerLimit=0;
     for(int i=this->getBoundingBoxHeight()-1;i>=0;i--){ // Fill the 2d Grid with fChar
        for(int j=lowerLimit;j<=upperLimit;j++){
            twoDimensionGrid[i][j]=fChar;
        }
        ++lowerLimit;
        --upperLimit;
     }


    return twoDimensionGrid;
}
