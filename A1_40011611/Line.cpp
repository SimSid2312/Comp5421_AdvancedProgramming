#include<iostream>
#include <cstring> 
#include "Line.h"
using std::cout;
using std::cin;
using std::endl;
using std::ostream;
using std::istream;
/**
	Assignment 1, Line.cpp
	Purpose: The is the implmentation of class Line and it models a line of text,storing it in a dynamically created array of characters 
	and providing simple operation on that line.
	@author Simran Sidhu
*/

/*
Constructs this line,assiging linePtr a pointer to deep copy of the supplied C-string text
@ text A pointer to constant array of charater (c-style string)
*/
Line::Line(const char* text) {
	
	lineLength = strlen(text);//strlen doesnot counts null terminator.
	capacity = strlen(text);	
	//dynamically allocating memory and assinging to linePtr
	//A deep copy means actually creating a new array and copying over the values.
	linePtr = new char[lineLength + 1]; //+1 to accomodate the null terminator
	// copy the content of text in linePtr
	int count = 0;
	while (count < lineLength) {
		linePtr[count] = text[count];
		count++;
	}
	linePtr[count] = '\0';//Append the null terminating character
	
}



/*
copy constructor
@ line_obj A reference of the line object whose content is to be copied
*/
Line::Line(const Line & line_obj) {

	 
	if (line_obj.empty()) {	//checking if this line is empty 
		return;
	}
	lineLength = line_obj.lineLength;
	capacity = line_obj.capacity;
	linePtr = new char[lineLength + 1];//dynamically allocating memory and assinging to linePtr
	int count = 0;
	while (count < lineLength) {
		linePtr[count] = line_obj.linePtr[count];
		count++;
	}
	linePtr[count] = '\0';//Append the null terminating character
}

/*
Destructor of the Line class, will empty the line and dellocate the memory allocated dynamically to the char array pointed by linePtr and resets
the line's length and capacity to zero
*/
Line::~Line() {

	while (!this->empty()) {
		pop_back();
	}

	delete [] linePtr;
	lineLength = 0;
	capacity = 0;
}

/*
Return the c-style version of this line
@ return A pointer to constant array of charater (c-style string)
*/
const char * Line::cstr() const {// 
	return linePtr;
}

/*
Returns whether this line is empty
@ return true(1) if this line object is empty , false(0) otherwise
*/
bool Line::empty() const {
	if (linePtr == nullptr || length()==0) {
		return true;
	}
	return false;
}

/*
Returns the length of this line
@ return the length of the c-style string
*/
int Line::length() const {
	return lineLength;
}

/*
Removes the last character in this line
*/
void Line::pop_back() {

	if (this->empty()) {
		return; //return as the line is empty
	}
	char * tempPtr = new char[lineLength + 1]; //back up the array of char (c-style string) pointed by linePtr 
	
	
	int count = 0;
	while (count < lineLength) {
		tempPtr[count] = linePtr[count];
		count++;
	}
	tempPtr[count] = '\0';	

	delete[] linePtr; //de-allocate the previously dynamically allocate space - linePtr
	linePtr = new char[lineLength]; // allocate the space dynamically again - with one less character space
	
	int counter = 0;
	for (; counter < lineLength - 1; counter++) { //Populate the new character array  from backup character of array
		linePtr[counter] = tempPtr[counter];
	}
	linePtr[counter] = '\0'; //Add the null terminating character
	lineLength--; // Decrement the lineLength
	
	delete[] tempPtr; //De-allocate the  space allocated to tempPtr
}

/*
Appends the character ch to the end of this line and if the line is full - the line is resized i.e  capacity is doubled
and new character is appended to the line's content.
@ ch  , The character to be appended to this line
*/
void Line::push_back(const char & ch) { 
	
	if (full()) { 
		resize();//Double the capacity as the line's length is full
		
		//Backing up of linePtr's pointed to char array
		char *tempPtr = new char[lineLength + 1]; 
		//strcpy_s(tempPtr, lineLength + 1, linePtr);
	
		int count = 0;
		while (count < lineLength) {
			tempPtr[count] = linePtr[count];
			count++;
		}
		tempPtr[count] = '\0';//Append the null terminating character
	
		//deallocate the current linePtr
		delete[] linePtr; 
		linePtr = new char[capacity]; //allocate the increased space to the linePtr pointed to char array dynamically
		
		int counter = 0;
		for (; counter < lineLength; counter++) { //Populate the new char array with the Backup line's content 
			linePtr[counter] = tempPtr[counter];
		}
		linePtr[lineLength] = ch;//Append the character
		lineLength += 1;//Increment the line Length by 1
		linePtr[lineLength] = '\0'; // Append the null terminating character to this c-style string
	
		delete [] tempPtr; // de-allocate the memory allocated to the char array Pointed to by tempPtr
	}
	else {
		//simply append to the line and increment the lineLength by 1		
		linePtr[lineLength] = ch;
		lineLength += 1;
		linePtr[lineLength] = '\0';//Append the null terminating character		
	}	
}


/*
	Assignment operator - Overloading Operator (=)
	@return const Line Object
*/
const Line & Line::operator=(const Line &line_obj) { 

	if (this == &(line_obj)) { 	//check : LHS!= RHS 
		return *this; 
	}
	//deallocate space used by "this" object
	while (!empty()) {
		pop_back();
	}	
	delete[] linePtr; // Deallocate Heap memory 	 
	lineLength = line_obj.lineLength; //copy the line_obj's lineLength to this line's lineLength
	capacity = line_obj.capacity;//copy the line_obj's capacity to this line's capacity 
	linePtr = new char[lineLength + 1];// Making new allocation of memory dynamically for char array
	//strcpy_s(linePtr, lineLength + 1, line_obj.linePtr);
	//copy the line_obj's char array content to char array pointed by this line's linePtr 
	int count = 0;
	while (count < lineLength) {
		linePtr[count] = line_obj.linePtr[count];
		count++;
	}
	linePtr[count] = '\0';//Append the null terminating character
	return *this; //return this object
}

/*
Operator Overloading of operator (==)
@return true(1) if str1 is equal to str2 otherwise false(0)
*/
bool operator== (const Line &lin_obj1, const Line &lin_obj2) {
	if (strcmp(lin_obj1.cstr(), lin_obj2.cstr()) == 0) { //strcmp function return value = 0 then it indicates str1 is equal to str2.
		return true;
	}
	return false;
}

/*
Operator Overloading of operator (!=)
@return true(1) if str1 is not equal to str2 otherwise false(0)
*/

bool operator!= (const Line &lin_obj1, const Line &lin_obj2) {
	if(strcmp(lin_obj1.cstr(), lin_obj2.cstr())!=0)  { // strcmp returning a value != 0 indicates the two cstyle strings are not equal
		return true;
	}
	return false;
}

/*
Returns whether this line is full
@return true(1)  if the this line's lineLength is equal to capacity (this happens when the line object was created) or  line's length is equal to capacity-1
this is seen when the line is already resize atleast once and the last element of the line is reserved for the null terminating character of c-style strings; 
otherwise returns false(0)
*/
bool Line::full() const {
	if ( lineLength == capacity || lineLength == capacity-1) {
		return true;
	}
	return false;
}

/*
Return the capacity of this line
@return capacity 
*/
int Line::getCapacity() const {
	return capacity;
}

/*
Doubles the capacity if the line is full- {if (full) then double storage capacity preserving current content}
*/
void Line::resize() {
	if (this->full()) {
		capacity *= 2;
	}
}

/*
Operator Overloading of operator (<<) to output datamembers of line's object
@out , reference of the object of ostream
@line_obj , reference of the line object 
@return reference of ostream object
*/
std::ostream& operator<<(std::ostream& out, const Line& line_obj) {
	out << "length of the line : " << line_obj.lineLength << endl;
	out << "capactity of the line: " << line_obj.capacity << endl;
	out << "line content :" << line_obj.linePtr << endl;
	return out;
}

/*
Operator Overloading of operator (>>) this function takes input from the user  about the lineLength and line content
@in , reference of the object of istream
@line_obj , reference of the line object
@return reference of istream object
*/
istream& operator>>(istream& in, Line& line_obj) {
	cout << "Enter length of the line"<< endl; //Taking input from the user for the length of the line
	in >> line_obj.lineLength; //User input of length is set to this line's line length
	line_obj.capacity = line_obj.lineLength; //User input of length is set to this line's line capacity
	line_obj.linePtr = new char[line_obj.lineLength + 1]; //dynamically allocating memory to the char array
	cout << "Enter a string to be set to the line :" << endl;
	int count = 0;
	while (count < line_obj.lineLength) { //Populating the char array with user provided string 
		in >> line_obj.linePtr[count];
		count++;
	}
	line_obj.linePtr[count] = '\0'; // Appending null terminating character to the c-stry string
	return in;
}

