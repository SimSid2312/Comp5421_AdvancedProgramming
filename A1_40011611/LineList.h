#pragma once
#include "Line.h"
/**
	Assignment 1, LineList.h
	Purpose: This file is the HeaderFile for class LineList whose implementation is in LineList.cpp
	@author Simran Sidhu
*/

class LineList {
	private:
		int theSize;// Number of elements in this list	
		class Node; //Private member type (an inner class)
		Node * head;// Pointer to the first node in this list
		Node * tail;//Pointer to the last node in this list
	public:
		LineList(); //default constructor
		virtual ~LineList();//destructor
		LineList(const LineList&); //copy constructor
		const LineList & operator=(const LineList&);//copy assignment
		void print() const; //Print this list
		void push_front(const Line&);//Inserts the line at the front of this list
		void push_back(const Line&);//Inserts the line at the end of this list
		void pop_front();//Removes the first node in this list
		void pop_back();//Removes the last node in this list
		int size() const; //Returns the size of this list
		bool empty() const;//Returns whether this list is empty
		void insert(const Line &, int); // Inserts a new line at position k in this list
		void remove(int);//Removes node at position k in this list
		Line get(int) const; //Returns the line at position k in this list
};