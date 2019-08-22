#include"Rectangle.h"
using std::vector;
/**
	Assignment 4, Rectangle.cpp
	Purpose: Class Rectangle (Concrete Class) is derived class of class Shape
             Rectangle.cpp is implementation of Rectangle.h headerfile
	@author Simran Sidhu
*/

/*
Paramterized ctor to initiate an Rectangle object and it calls the base class(Shape) ctor passing in the name and description
@ wd constant reference to a double holding the width
@ ht constant reference to a double holding the height
@ name const reference to a string holding name of the shape object
@ description const reference to a string holding description of the shape object
*/
Rectangle::Rectangle(const double & wd,const double & ht,
                     const string & name,const string & description) : width(wd), height(ht),Shape(name,description){}

/*
Return the width
@return (double) width of the shape object - Rectangle
*/
double Rectangle::getWidth() const{
    return this->width;
}

/*
Return the height
@return (double) height of the shape object - Rectangle
*/
double Rectangle::getHeight() const{
    return this->height;
}

/*
Computes geometric area
@return (double) geometric area of the shape object - Rectangle
*/
double Rectangle::computeGeometricArea() const{
    double geometricArea=this->height * this->width;
    return this->roundOff(geometricArea);
}

/*
Computes geometric perimeter
@return (double) geometric perimeter of the shape object - Rectangle
*/
double Rectangle::computeGeometricPerimeter() const{
    double geometricPerimeter=2*(this->height+this->width);
    return this->roundOff(geometricPerimeter);
}
/*
Computes screen area
@return (int) screen area of the shape object - Rectangle
*/
int Rectangle::computeScreenArea() const{
    int screenArea= this->height * this->width;
    return screenArea;
}
/*
Computes screen perimeter
@return (int) screen perimeter of the shape object - Rectangle
*/
int Rectangle::computeScreenPerimeter() const{
    int screenPerimeter= 2*(this->height+this->width) - 4;
    return screenPerimeter;
}

/*
Returns height of the bounding box
@return (int) height of the bounding box of the shape object - Rectangle
*/
int Rectangle::getBoundingBoxHeight() const{
    return this->height;
}
/*
Returns width of the bounding box
@return (int) width of the bounding box of the shape object - Rectangle
*/
int Rectangle::getBoundingBoxWidth() const{
    return this->width;
}
/*
Draws a textual image for the shape object on a two dimensional grid and returns that grid
@return (vector<vector<char>>)  two dimensional grid of textual image for the shape object - Rectangle
*/
vector<vector<char>> Rectangle::draw(char fChar,char bChar) const{
    vector<vector<char>> twoDimensionGrid;
     for(int i=0;i<this->getBoundingBoxHeight();i++){
        vector<char> gridRow;
        for(int j=0;j<this->getBoundingBoxWidth();j++){
            gridRow.push_back(fChar);
        }
        twoDimensionGrid.push_back(gridRow);
     }
    return twoDimensionGrid;
}


















