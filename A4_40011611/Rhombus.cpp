#include <cmath>
#include<iostream>
#include "Rhombus.h"
using std::cout;
using std::endl;
/**
	Assignment 4, Rhombus.cpp
	Purpose: Class Rhombus(Concrete Class) is derived class of class Shape
             Rhombus.cpp is implementation of Rhombus.h headerfile
	@author Simran Sidhu
*/

/*
Paramterized ctor to initiate an Rhombus object and it calls the base class(Shape) ctor passing in the name and description
@ d1 constant reference to a double holding the width/height of bounding box
@ name const reference to a string holding name of the shape object
@ description const reference to a string holding description of the shape object
*/
Rhombus::Rhombus(const double & d1,
                const string & name,
                const string & description) : d(std::fmod(d1,2)==0 ? d1+1:d1),Shape(name,description)
{};

/*
Computes geometric area
@return (double) geometric area of the shape object - Rhombus
*/
double Rhombus::computeGeometricArea() const{
    double geometricArea= (this->d * this->d)/2;
    return this->roundOff(geometricArea);
}
/*
Computes geometric perimeter
@return (double) geometric perimeter of the shape object - Rhombus
*/
double Rhombus::computeGeometricPerimeter() const{
    double geometricPerimeter=(2*sqrt(2))*this->d;
    return this->roundOff(geometricPerimeter);
}
/*
Computes screen area
@return (int) screen area of the shape object - Rhombus
*/
int Rhombus::computeScreenArea() const{
    int screenArea=(2*floor(d/2)*(floor(d/2)+1))+1;
    return screenArea;

}
/*
Computes screen perimeter
@return (int) screen perimeter of the shape object - Rhombus
*/
int Rhombus::computeScreenPerimeter() const{
    int screenPerimeter=2*(this->d - 1 );
    return screenPerimeter;
}
/*
Returns height of the bounding box
@return (int) height of the bounding box of the shape object - Rhombus
*/
int Rhombus::getBoundingBoxHeight() const{
    return this->d;
}

/*
Returns width of the bounding box
@return (int) width of the bounding box of the shape object - Rhombus
*/
int Rhombus::getBoundingBoxWidth() const {
    return this->d;
}
/*
Draws a textual image for the shape object on a two dimensional grid and returns that grid
@return (vector<vector<char>>)  two dimensional grid of textual image for the shape object - Rhombus
*/
vector<vector<char>> Rhombus::draw(char fChar,char bChar) const{
    vector<vector<char>> twoDimensionGrid;
    int midPointOnHeight=floor(this->getBoundingBoxHeight()/2);
    int midPointOnWidth=floor(this->getBoundingBoxWidth()/2);
    int midPointOnWidthLowerLimit=midPointOnWidth;
    int midPointOnWidthUpperLimit=midPointOnWidth;

    //Filling the 2d Grid
    for(int i=0;i<this->getBoundingBoxHeight();i++){
        vector<char> gridRow;
        if(i<midPointOnHeight){
            for(int j=0;j<this->getBoundingBoxWidth();j++){
                 if( j < midPointOnWidthLowerLimit || j > midPointOnWidthUpperLimit){
                    gridRow.push_back(bChar);
                 }
                 else{
                    gridRow.push_back(fChar);
                 }

            }
            twoDimensionGrid.push_back(gridRow);
            --midPointOnWidthLowerLimit;
            ++midPointOnWidthUpperLimit;

        }
        if (i>midPointOnHeight){
            ++midPointOnWidthLowerLimit;
            --midPointOnWidthUpperLimit;
            for(int j=0;j<this->getBoundingBoxWidth();++j){
              if(j < midPointOnWidthLowerLimit || j > midPointOnWidthUpperLimit){
                gridRow.push_back(bChar);

              }else{
                gridRow.push_back(fChar);

              }

          }
          twoDimensionGrid.push_back(gridRow);
        }
        else if (i==midPointOnHeight){
            for(int j=0;j<this->getBoundingBoxWidth();++j){
                gridRow.push_back(fChar);

            }
            midPointOnWidthLowerLimit=0;
            midPointOnWidthUpperLimit=this->getBoundingBoxWidth()-1;
           twoDimensionGrid.push_back(gridRow);
        }

    }

    return twoDimensionGrid;


}
