#ifndef SHAPE_H
#define SHAPE_H
#include<iostream>
#include <string.h>
#include <vector>
using std::ostream;
using std::string;
using std::vector;
/**
	Assignment 4, Shape.h
	Purpose: Header File for class Shape which is an abstract class.
	@author Simran Sidhu
*/
class Shape{
    private:
        int id; //id of the shape object
        string name; // name of the shape object
        string description; // description of the shape object
       
    public :
        static int identityNumber; // static member of the class helps to issue a new unique id to every new shape object 
         
        Shape(const string  & , const string  &);//Parameterized ctor
        int getId() const; //get  id
        string getName() const; //get name
        string getDescription() const;//get description
        void setName(const string & name);//sets name 
        void setDescription(const string & description);//set description
        const string toString() const;//Generates and returns a string representation of the shape object
        //Pure virtual functions - atleast one such function is a must to make this class abstract
        virtual double computeGeometricArea() const=0;//computes geometric area 
        virtual double computeGeometricPerimeter() const=0;// computes geometric perimeter
        virtual int computeScreenArea() const=0;// compute screen area - number of characters forming textual image of shape
        virtual int computeScreenPerimeter() const=0;// computes screen perimeter - number of character on border of textual image of shape
        virtual vector<vector<char>> draw(char fChar='*',char bChar=' ') const =0;//draws a textual image for the shape object on a two dimensional grid and returns that grid
        virtual int getBoundingBoxHeight() const =0;//returns height of the bounding box
        virtual int getBoundingBoxWidth() const=0;//returns width of the bounding box
        double roundOff(double d) const;//rounds of the result of computeGeometricArea and computeGeometricPerimeter upto 2 decimal places and returns it
        friend ostream& operator<<(ostream& out,const Shape & sh);//overloads operator << as a friend

};
#endif
