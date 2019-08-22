#include <iostream>
#include<typeinfo>
#include<iomanip>
#include<string>
#include <cmath>
#include "Shape.h"
#include <sstream>
using std::cout;
using std::cin;
using std::endl;
using std::setw;
using std::string;
using std::to_string;
using std::size_t;
using std::stod;

/**
	Assignment 4, Shape.cpp
	Purpose: Class Shape is an abstract class.
             Shape.cpp is implementation of Shape.h headerfile
	@author Simran Sidhu
*/

int Shape::identityNumber=0;// Initializing the static variable

/*
Paramterized ctor - set the name and description of the shape object. It also increments static variable - identityNumber
and set it as id for a shape object,
@ b1 constant reference to a double holding the width of bounding box
@ name const reference to a string holding name of the shape object
@ description const reference to a string holding description of the shape object
*/
Shape::Shape(const string  & name, const string & description) :  name(name),description(description){
    ++identityNumber;//Increase the id everytime a new shape is created.
    this->id=identityNumber; //Sets the id for a Shape Object
}

/*
Return the id of the shape object
@return (int) id of the shape object
*/
int Shape::getId() const{
    return this->id;
}

/*
Return the name of the shape object
@return (string) name of the shape object
*/
string Shape::getName() const{
    return this->name;
}

/*
Return the description of the shape object
@return (string) description of the shape object
*/
string Shape::getDescription() const{
    return this->description;
}

/*
Sets the name of the shape object
@name const reference to a string holding name of the shape object
*/
void Shape::setName(const string & name){
    this->name=name;
}
/*
Sets the description of the shape object
@name const reference to a string holding description of the shape object
*/
void Shape::setDescription(const string & description){
    this->description=description;
}

/*
Generates and returns a string representation of the shape object
@return (string) a string representation of the shape object
*/
const string Shape::toString() const{
    std::ostringstream geoArea,geoPerimeter,spacing;
    geoArea << std::fixed << std::setprecision(2) << this->computeGeometricArea();//Setting precision to 2 decimal places
    geoPerimeter << std::fixed << std::setprecision(2) << this->computeGeometricPerimeter();//Setting precision to 2 decimal places
    spacing << setw(2) << " ";

    std::string result("Shape Information\n");
    result+="-----------------\n";
    result+="id:           ";
    result+=spacing.str();
    result+=std::to_string(this->getId());
    result+="\nShape name:   ";
    result+=spacing.str();
    result+=this->getName();
    result+="\nDescription:  ";
    result+=spacing.str();
    result+=this->getDescription();
    result+="\nB. box width: ";
    result+=spacing.str();
    result+=std::to_string(this->getBoundingBoxWidth());
    result+="\nB. box height:";
    result+=spacing.str();
    result+=std::to_string(this->getBoundingBoxHeight());
    result+="\nScr area:     ";
    result+=spacing.str();
    result+=std::to_string(this->computeScreenArea());
    result+="\nGeo area:     ";
    result+=spacing.str();
    result+=geoArea.str();
    result+="\nScr Perimeter:";
    result+=spacing.str();
    result+=std::to_string(this->computeScreenPerimeter());
    result+="\nGeo Perimeter:";
    result+=spacing.str();
    result+=geoPerimeter.str();
    result+="\nStatic type:  ";
    result+=spacing.str();
    result+=typeid(this).name();
    result+="\nDynamic type: ";
    result+=spacing.str();
    result+=typeid(*this).name();
    result+="\n";
    return result;
}

/*
Operator Overloading of operator (<<) to output datamembers of Shape's object
@out , reference of the object of ostream
@sh , reference of the Shape object
@return reference of ostream object
*/
ostream& operator<<(ostream& out,const Shape & sh){
    out << sh.toString();
    return out;

}

/*
Rounds of the result of computeGeometricArea and computeGeometricPerimeter upto 2 decimal places and returns it
@return (double) result of computeGeometricArea and computeGeometricPerimeter upto 2 decimal places
*/
double Shape::roundOff(double d) const{
    int temp = (int)(d *1000.0);
    int last_num= temp%10;
    if(last_num>5){
        int updateSecondLast= ((temp%100)/10)+1;
        string num_str= to_string(temp);
        int pos= (num_str.length()-2) ;
        num_str.replace(pos ,1,to_string(updateSecondLast));
        temp= stoi(num_str);
}
double updatedTemp = ((double)temp) / 1000.0;
string temp_str= to_string(updatedTemp);
size_t decimal_pos = temp_str.find('.');
string final_str = temp_str.substr (0,decimal_pos+3);
return stod(final_str);
}



