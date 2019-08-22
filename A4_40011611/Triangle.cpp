#include "Triangle.h"
/**
	Assignment 4, Triangle.cpp
	Purpose: Class Triangle(abstract Class) is a derived class of Shape and a base class for AcuteTriangle and RightTriangle
             Traingle.cpp is implementation of Triangle.h headerfile
	@author Simran Sidhu
*/

/*
Paramterized ctor to initiate an Triangle object and it calls the base class(Shape) ctor passing in the name and description
@ name const reference to a string holding name of the shape object
@ description const reference to a string holding description of the shape object
*/
Triangle::Triangle(const string & name, const string &description):Shape(name,description){};
