#include "Triangle.h"
#include <vector>
using std::vector;
/**
	Assignment 4, AcuteTriangle.h
	Purpose: Header File for class AcuteTriangle which is a derived class of base class Triangle
	@author Simran Sidhu
*/
class AcuteTriangle : public Triangle{
    private:
        double b; //Height and Width of bounding box
    public:
        AcuteTriangle(const double &,
                      const string & = "Acute triangle",
                     const string & = "All acute angles"); //Paramterized ctor
       double computeGeometricArea()const;//computes geometric area
       double computeGeometricPerimeter()const; // computes geometric perimeter
       int computeScreenArea()const; // compute screen area - number of characters forming textual image of shape
       int computeScreenPerimeter()const; // computes screen perimeter - number of character on border of textual image of shape
       int getBoundingBoxHeight() const;//returns height of the bounding box
       int getBoundingBoxWidth() const;//returns width of the bounding box
       vector<vector<char>> draw(char fChar='*',char bChar=' ') const; //draws a textual image for the shape object on a two dimensional grid and returns that grid
};
