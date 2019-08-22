#include <vector>
#include "Triangle.h"
using std::vector;
/**
Assignment 4, RightTriangle.h
Purpose: Header File for class RightTriangle which is a derived class of base class Triangle
@author Simran Sidhu
*/
class RightTriangle : public Triangle{
    private:
        double b; //height and width of bounding box
    public :

       RightTriangle(const double &,
                     const string & = "Right traingle",
                     const string & = "One right and two acute angles"); //Paramterized ctor
       double computeGeometricArea()const;//computes geometric area
       double computeGeometricPerimeter()const; // computes geometric perimeter
       int computeScreenArea()const; // compute screen area - number of characters forming textual image of shape
       int computeScreenPerimeter()const; // computes screen perimeter - number of character on border of textual image of shape
       int getBoundingBoxHeight() const; //returns height of the bounding box
       int getBoundingBoxWidth() const; //returns width of the bounding box
       vector<vector<char>> draw(char fChar='*',char bChar=' ') const;//draws a textual image for the shape object on a two dimensional grid and returns that grid



};
