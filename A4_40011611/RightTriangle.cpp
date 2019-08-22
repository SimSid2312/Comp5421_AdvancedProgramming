#include<cmath>
#include "RightTriangle.h"
using std::vector;
/**
	Assignment 4, RightTriangle.cpp
	Purpose: Class RightTriangle(Concrete Class) is derived class of class Triangle
             RightTriangle.cpp is implementation of RightTriangle.h headerfile
	@author Simran Sidhu
*/

/*
Paramterized ctor to initiate an Right Triangle object and it calls the base class(Triangle) ctor passing in the name and description
@ b1 constant reference to a double holding the width of bounding box
@ name const reference to a string holding name of the shape object
@ description const reference to a string holding description of the shape object
*/
RightTriangle::RightTriangle(const double & b1,
                     const string &name,
                     const string & description):b(b1),Triangle(name,description){};

/*
Computes geometric area
@return (double) geometric area of the shape object - Right Triangle
*/
double RightTriangle::computeGeometricArea() const{
    double geometricArea= (this->b*this->b)/2;
    return this->roundOff(geometricArea);

}
/*
Computes geometric perimeter
@return (double) geometric perimeter of the shape object - Right Triangle
*/
double RightTriangle::computeGeometricPerimeter() const{
    double geometricPerimeter = (2+sqrt(2))*this->b;
    return this->roundOff(geometricPerimeter);
}
/*
Computes screen area
@return (int) screen area of the shape object - Right Triangle
*/
int RightTriangle::computeScreenArea()const{
    int screenArea=(this->b*(this->b+1))/2;
    return screenArea;
}

/*
Computes screen perimeter
@return (int) screen perimeter of the shape object - Right Triangle
*/
int RightTriangle::computeScreenPerimeter() const{
    int screenPerimeter=3*(this->b-1);
    return screenPerimeter;
}
/*
Returns height of the bounding box
@return (int) height of the bounding box of the shape object - Right Triangle
*/
int RightTriangle::getBoundingBoxHeight() const{
    return this->b;
}
/*
Returns width of the bounding box
@return (int) width of the bounding box of the shape object - Right Triangle
*/
int RightTriangle::getBoundingBoxWidth() const{
    return this->b;
}
/*
Draws a textual image for the shape object on a two dimensional grid and returns that grid
@return (vector<vector<char>>)  two dimensional grid of textual image for the shape object - Right Triangle
*/
vector<vector<char>> RightTriangle::draw(char fChar,char bChar) const{
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
     for(int i=this->getBoundingBoxHeight()-1;i>=0;i--){ // Fill the 2d Grid with fChar
        for(int j=0;j<=upperLimit;j++){
            twoDimensionGrid[i][j]=fChar;
        }
        --upperLimit;
     }


    return twoDimensionGrid;
}
