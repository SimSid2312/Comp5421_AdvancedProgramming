#include <vector>
#include"Shape.h"
using std::vector;
/**
	Assignment 4, Rectangle.h
	Purpose: Header File for class Rectangle which is a derived class of base class Shape
	@author Simran Sidhu
*/
class Rectangle : public Shape{
    private:
            double width; //Width of bounding box
            double height; //Height of bounding box

    public:
        Rectangle(const double &,const double & ,
                const string & ="Four-sided",
                const string & ="Four right angles"); //Paramterized ctor

        double getWidth() const; // returns width
        double getHeight() const; // returns height
        double computeGeometricArea() const; //computes geometric area
        double computeGeometricPerimeter() const; // computes geometric perimeter
        int computeScreenArea() const; // compute screen area - number of characters forming textual image of shape
        int computeScreenPerimeter() const; // computes screen perimeter - number of character on border of textual image of shape
        int getBoundingBoxHeight() const; //returns height of the bounding box
        int getBoundingBoxWidth() const; //returns width of the bounding box
        vector<vector<char>> draw(char fChar='*',char bChar=' ') const; //draws a textual image for the shape object on a two dimensional grid and returns that grid



};
