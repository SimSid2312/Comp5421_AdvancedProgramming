#include <vector>
#include"Shape.h"
using std::vector;
/**
	Assignment 4, Rhombus.h
	Purpose: Header File for class Rhombus which is a derived class of base class Shape	
	@author Simran Sidhu
*/
class Rhombus : public Shape{
    private:
         double d;//height and width of bounding box
    public:
        Rhombus(const double &,
                const string & ="Diamond",
                const string & = "A parallelogram with equal sides"); //Paramterized ctor

        vector<vector<char>> draw(char fChar='*',char bChar=' ') const; //draws a textual image for the shape object on a two dimensional grid and returns that grid
        double computeGeometricArea()const; //computes geometric area
        double computeGeometricPerimeter()const; // computes geometric perimeter
        int computeScreenArea()const; // compute screen area - number of characters forming textual image of shape
        int computeScreenPerimeter() const; // computes screen perimeter - number of character on border of textual image of shape
        int getBoundingBoxHeight() const; //returns height of the bounding box
        int getBoundingBoxWidth() const;  //returns width of the bounding box

};

