#pragma once
#include<iostream>
/**
	Assignment 1, Line.h
	Purpose: This file is the HeaderFile for the class Line whose implementation is in Line.cpp
	@author Simran Sidhu
*/
class Line {	
	private:
		char * linePtr;//stores a pointer to the first character in a dynamically created array of char, effectively representing the underlying line of text
		int lineLength;//length of this line
		int capacity;//storage capacity of this line
	public:
		Line () =default; // default constructor
		Line(const char*);//Constructs this line,assiging linePtr a pointer to deep copy of the supplied C-string text
		Line(const Line &); //copy constructor
		const Line & operator=(const Line &); //assignment operator
		virtual ~Line();//Desctructor
		const char * cstr() const; // return the c-style version of this line
		int length() const; //return the length of this line
		bool empty() const; // returns whether this line is empty
		bool full() const; //returns whether this line is full
		int getCapacity() const; //returns the capacity of this line
		void resize();//doubles the capacity if the line is full- {if (full) then double storage capacity preserving current content}
		void push_back(const char & ch);//appends the ch to the end of this line
		void pop_back();//removes the last character in this line
		friend std::ostream& operator<<(std::ostream&, const Line&);//overloads operator << as a friend
		friend std::istream& operator>>(std::istream&, Line&);//overloads operator >> as friend
};

bool operator== (const Line &, const Line &);//free function which implements operator overloading of operator ==
bool operator!= (const Line &, const Line &); //free function which implements operator overloading of operator !=