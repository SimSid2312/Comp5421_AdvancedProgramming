#ifndef TRIANGLE_H
#define TRIANGLE_H
#include "Shape.h"
/**
	Assignment 4, Triangle.h
	Purpose: Header File for class Triangle which is a derived class of Shape and a base class for AcuteTriangle and RightTriangle
	@author Simran Sidhu
*/
class Triangle : public Shape{
    public:
       Triangle(const string & , const string &);//Parameterized ctor
};
#endif
