#include <memory>
#include<array>
#include "Shape.h"
/**
Assignment 4, SlotMachine.h
Purpose: Header File for class SlotMachine, for Task 2 of 2
@author Simran Sidhu
*/
class SlotMachine{
    private:
        std::array<std::unique_ptr<Shape>,3> reel{};//Array of three C++ smart pointer that are assigned Shape objects
        void make_shapes(); //Step 4 , makes the shapes for each of 3 Shape object
        void make_shapes(int k); //Step 5 - 6 , controlled/called by make_shape() member function  to generate the shape
        void display();// displaying the shapes
        string cleanupUserInput(const string &);//Validates and removed any leading and trailing spaces in user input of Bet
        int checkShapeNames(const string &,const string &, const string &);//Checks and compares if two or more shape name are same
        bool compareMiddleScreenArea(const int &,const int &,const int &);//Checks if the Screen Area of Middle >  Screen Area of Left + Screen Area of Right
        bool checkLeftRightShapes(const string &,const string &);//Checks if the left and right Shapes are similar in shape
        bool checkTwoScreenAreaMatch(const int &,const int &,const int &);//Checks if any two shapes have same screen area

    public:
        SlotMachine()=default;//default ctor
        SlotMachine(const SlotMachine &) = delete;//copy ctor
        SlotMachine(SlotMachine &&) = delete;//move ctor
        SlotMachine &operator=(const SlotMachine &) = delete; //copy assignment
        SlotMachine &operator=(SlotMachine &&) = delete;//move assignment
        virtual ~SlotMachine()=default;//dtor
        void run();// initiates and runs the slot machine algorithm
};
