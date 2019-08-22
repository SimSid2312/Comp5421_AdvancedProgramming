#include <iostream>
#include<string>
#include <time.h>
#include<cstdlib>
#include "SlotMachine.h"
#include "Rhombus.h"
#include "AcuteTriangle.h"
#include "RightTriangle.h"
#include "Rectangle.h"
using std::cout;
using std::cin;
using std::endl;
using std::string;
using std::getline;
using std::size_t;
using std::stoi;
using std::ostream;
using Grid = vector<vector<char>>;
/**
	Assignment 4, SlotMachine.cpp
	Purpose: Class SlotMachine
             SlotMachine.cpp is implementation of LineEd.h headerfile
	@author Simran Sidhu
*/

/*
Displaying the shapes
*/
void SlotMachine::display(){

    Grid box_0=this->reel[0]->draw();
    Grid box_1= this->reel[1]->draw();
    Grid box_2= this->reel[2] ->draw();
    //cout << "---- box height: ---" << endl;
    int box_0Height=this->reel[0] ->getBoundingBoxHeight();//a
    int box_1Height=this->reel[1] ->getBoundingBoxHeight();//b
    int box_2Height=this->reel[2] ->getBoundingBoxHeight();//c
    int maxHeight;
    int rows;
    //cout << box_0Height << " " <<  box_1Height << " "  << box_2Height << endl;
     if(box_0Height > box_1Height){
        maxHeight=(box_0Height > box_2Height) ? box_0Height : box_2Height;
    }
    else {
        maxHeight=(box_1Height>box_2Height)? box_1Height : box_2Height;

    }
    //cout << "Max height : " << maxHeight << endl;
    rows= maxHeight+2;

    //cout << "----Box Width : ----" << endl;
    int box_0Width = this->reel[0] ->getBoundingBoxWidth();
    int box_1Width = this->reel[1] ->getBoundingBoxWidth();
    int box_2Width = this->reel[2] ->getBoundingBoxWidth();
    //cout << box_0Width << " " << box_1Width << " " << box_2Width << endl;
    int columns=box_0Width+box_1Width+box_2Width+10;
    //cout << "Columns : " << columns <<endl;

    //cout << "---making a grid :-----"<< endl;
    Grid outBox;
    for(int i=0;i<rows;i++){ //Basic Build up - outBox just borders
            vector<char> outBoxRow;
        for(int j=0;j<columns;j++){
            if( (i==0 && j==0) || (i==0 && j==columns-1) || (i==rows-1 && j==0) || (i==rows-1 && j==columns-1) ){
                //Border-Corners
                outBoxRow.push_back('+');
            }

            else if ( (j==0 && i !=0) || (j==columns-1 && i!=0) ){
                 //Left Border and Right Border
                outBoxRow.push_back('|');
            }
            else if ( (j==1 && i>0 && i <=rows-2 ) || (j==columns-2 && i>0 && i <=rows-2) ){
                //Blank Border of Extreme Left and Extreme Right
                outBoxRow.push_back(' ');
            }
            else if ( (i==0 && (j!=0 || j!=columns-1)) ||  (i==rows-1 && (j!=0 || j!=columns-1) )     ){
                outBoxRow.push_back('-');
            }

            else{
                outBoxRow.push_back('.');
            }

        }
            outBox.push_back(outBoxRow);
    }


    //---------------------------------------Fill up Box1 with first Shape ---------------------------------------
    for(int i=1;i<=rows-2;i++){
        for(int j=2;j<box_0Width+2;j++){
            //outBox[i][j]='1';
            if(i<=box_0Height){
               outBox[i][j]=box_0[i-1][j-2];
            }
            else{
                outBox[i][j]=' ';
            }
        }
    }

    //Code to add border and blank btw box0 and box1
    int endOfBox0=box_0Width+2;
    for(int i=1;i<=rows-2;i++){
        outBox[i][endOfBox0]=' ';
        outBox[i][endOfBox0+1]='|';
        outBox[i][endOfBox0+2]=' ';
    }
    //Updating the first and last element to + of the border
    outBox[0][endOfBox0+1]='+';
    outBox[rows-1][endOfBox0+1]='+';
    //----------------------------------------Fill up Box2 with second Shape-----------------------------------------
    for(int i=1;i<=rows-2;i++){
        for(int j=endOfBox0+3;j<box_1Width+endOfBox0+3;j++){
            if(i<=box_1Height){
               outBox[i][j]=box_1[i-1][j-(endOfBox0+3)];
            }
            else{
                outBox[i][j]=' ';
            }
        }
    }
    //Code to add border and blank btw box1 and box2
    int endOfBox1=box_1Width+endOfBox0+3;
    for(int i=1;i<=rows-2;i++){
        outBox[i][endOfBox1]=' ';
        outBox[i][endOfBox1+1]='|';
        outBox[i][endOfBox1+2]=' ';
    }
    //Updating the first and last element to + of the border
    outBox[0][endOfBox1+1]='+';
    outBox[rows-1][endOfBox1+1]='+';
    //---------------------------------------Fill up Box3 with third Shape ----------------------------------------
    for(int i=1;i<=rows-2;i++){
        for(int j=endOfBox1+3;j<box_2Width+endOfBox1+3;j++){
            if(i<=box_2Height){
               outBox[i][j]=box_2[i-1][j-(endOfBox1+3)];
            }
            else{
                outBox[i][j]=' ';
            }
        }

    }

    //---------------------------------------- Display----------------------------------------------
     for (const auto& row : outBox) // for each row vector in the grid
    {
       for (const auto& element : row) // for each element (char) in the row vector
       {
         cout << element;
       }
      cout << endl; // line break
   }

}

/*
Validates and removed any leading and trailing spaces in user input of Bet
@return (string) user input of Bet after removing leading and trailing spaces
*/
string SlotMachine::cleanupUserInput(const string & input){//Removes leading and trailing spaces
    string cleanedResult;
    const string whiteSpace = " \n\r\t\f\v";
    size_t foundInLeading = input.find_first_not_of(whiteSpace);//leading spaces
    if(foundInLeading==std::string::npos){
        cleanedResult= "";
    }
    else{
        cleanedResult=input.substr(foundInLeading);
        size_t foundInEnd = cleanedResult.find_last_not_of(whiteSpace);// trailing spaces
        if(foundInEnd == std::string::npos){
            cleanedResult= "";
        }
        else{
            cleanedResult=cleanedResult.substr(0, foundInEnd + 1);
        }

    }

    return cleanedResult;

}

/*
Slot Algorithm : Steps 5 - 6 , it controlled/called by make_shape() member function to generate the shape
@k is the shape number i.e 0,1,2 the three number represents the three shape objects
*/

void SlotMachine::make_shapes(int k){

        int n = rand()%4;//Generate a random integer n, 0<=n<=3
        //cout << n << endl;
        int w= (rand()%25)+1;//Generate a random width w, 1<=w<=25
        //cout <<  w << endl;
        if(n==0){
            //cout << "Make a rhombus" << endl;
            this->reel[k].reset(new Rhombus(w));
        }
        else if(n==1){
            //cout << "Make a Acute Triangle" << endl;
            this->reel[k].reset(new AcuteTriangle(w));
        }
        else if (n==2){
            //cout << "Make a Right Triangle" << endl;
            this->reel[k].reset(new RightTriangle(w));
        }
        else{
            //cout << "Make a Rectangle" << endl;
            int h= (rand()%25)+1;//Generate a random width h, 1<=h<=25
            //cout << "h:" << h << endl;
            this->reel[k].reset(new Rectangle(w,h));

        }
}

/*
Slot Algorithm : Step 4 , makes the shapes for each of 3 Shape object
*/
void SlotMachine::make_shapes(){
    srand((unsigned)time(0));
    for(int k=0;k<3;k++){
        make_shapes(k);
        //cout << "---" << endl;
    }
}

/*
Checks and compares if two or more shape name are same
@shape0Name const reference to a string holding name of the first shape object
@shape1Name const reference to a string holding name of the second shape object
@shape2Name const reference to a string holding name of the third shape object
@return (int) the count of the number of shapes that are similar
*/

int SlotMachine::checkShapeNames(const string & shape0Name,const string & shape1Name, const string & shape2Name){
    int equalStringCount=0;

    if( (shape0Name.compare(shape1Name) == 0 )&& (shape1Name.compare(shape2Name) == 0 ) ){
        equalStringCount=3;
    }
    else if ( (shape0Name.compare(shape1Name) == 0 )&& (shape1Name.compare(shape2Name) != 0 ) ){
        equalStringCount=2;
    }
    else if( (shape0Name.compare(shape1Name) != 0 )&& (shape1Name.compare(shape2Name) == 0 ) ){
        equalStringCount=2;
    }
    return equalStringCount;
}

/*
Checks if the Screen Area of Middle >  Screen Area of Left + Screen Area of Right
@shape0ScreenArea const reference to a int holding screen area of the first shape object
@shape1ScreenArea const reference to a int holding screen area of the second shape object
@shape2ScreenArea const reference to a int holding screen area of the third shape object
@return (bool) true if shape1ScreenArea is greater than the sum of shape0ScreenArea and shape2ScreenArea otherwise false
*/
bool SlotMachine::compareMiddleScreenArea(const int &shape0ScreenArea,const int & shape1ScreenArea,const int & shape2ScreenArea){

    return  (shape1ScreenArea > (shape0ScreenArea+shape2ScreenArea));
}

/*
Checks if the left and right Shapes are similar in shape by comparing their shape names
@shape0Name const reference to a string holding name of the first shape object
@shape2Name const reference to a string holding name of the third shape object
@return (bool) true if shape0Name is same as shape2Name otherwise false
*/
bool SlotMachine::checkLeftRightShapes(const string & shape0Name,const string &shape2Name){

        return (shape0Name.compare(shape2Name) == 0);
}

/*
Checks if any two shapes have same screen area
@shape0ScreenArea const reference to a int holding screen area of the first shape object
@shape1ScreenArea const reference to a int holding screen area of the second shape object
@shape2ScreenArea const reference to a int holding screen area of the third shape object
@return (bool) true if shape0ScreenArea is equal to shape1ScreenArea or shape0ScreenArea is equal to shape2ScreenArea
                 or shape1ScreenArea is equal to shape2ScreenArea otherwise false
*/

bool SlotMachine::checkTwoScreenAreaMatch(const int & shape0ScreenArea,const int & shape1ScreenArea,const int &shape2ScreenArea){
    bool match=false;
    if(shape0ScreenArea==shape1ScreenArea){
        match =true;
    }
    else if(shape0ScreenArea==shape2ScreenArea){
        match = true;
    }
    else if(shape1ScreenArea==shape2ScreenArea){
        match =true;
    }
    return match;
}
/*
Initiates and runs the slot machine algorithm
*/
void SlotMachine::run(){
    cout << "Welcome to 3-Reel Lucky Slot Machine Game!" << endl;
    cout << "Each reel will randomly display one of four shapes, each in 25 sizes." << endl;
    cout << "To win 3 x bet Get 2 similar shapes AND 2 shapes with equal Scr Areas" << endl;
    cout << "To win 2 x bet 3 similar shapes"<< endl;
    cout << "To win 1 x bet Get (Middle) Scr Area > (Left + Right) Scr Areas"<< endl;
    cout << "To win or lose nothing Get same Left and Right shapes"<< endl;
    cout << "Otherwise, you lose your bet." << endl;
    cout << "You start with 10 free slot tokens!"<< endl;

    int slotTokens=10;
    while(true){
        cout << "\nHow much would you like to bet (enter 0 to quit)? ";
        string userChoice;
        getline(cin,userChoice);
        userChoice=this->cleanupUserInput(userChoice);
        if(userChoice==""){ //Re-iterate
            continue; //Nothing entered skip this iteration
        }

        int userBet=stoi(userChoice);
        //cout << "userBet :" << userBet << endl;
        if(slotTokens==0 || userBet==0){ // Quit
            break;
        }

        if(userBet > slotTokens){ //Re-iterate
            cout << "You can't bet more than " << slotTokens << ", try again!"<< endl;
            continue; //Skip this turn and ask for bet again
        }

        if(userBet < 0){
            cout << "No negative bets, try again!" << endl;
            continue;
        }

        this->make_shapes();//Make the three Shapes
        this->display();//Display the shapes

        //----Slot Algorithm : Steps 19 - 21 , compute prize payout(token won),update token slots and display result on console---------
        string shape0Name=this->reel[0]->getName();
        int shape0ScreenArea= this->reel[0]->computeScreenArea();
        int shape0BoxHeight= this->reel[0]->getBoundingBoxHeight();
        int shape0BoxWidth= this->reel[0]->getBoundingBoxWidth();

        string shape1Name=this->reel[1]->getName();
        int shape1ScreenArea= this->reel[1]->computeScreenArea();
        int shape1BoxHeight= this->reel[1]->getBoundingBoxHeight();
        int shape1BoxWidth= this->reel[1]->getBoundingBoxWidth();


        string shape2Name= this->reel[2]->getName();
        int shape2ScreenArea= this->reel[2]->computeScreenArea();
        int shape2BoxHeight= this->reel[2]->getBoundingBoxHeight();
        int shape2BoxWidth= this->reel[2]->getBoundingBoxWidth();

        int countOfSimilarShapes=checkShapeNames(shape0Name,shape1Name,shape2Name);
        bool screenAreaMiddle=compareMiddleScreenArea(shape0ScreenArea,shape1ScreenArea,shape2ScreenArea);
        bool leftSimilarRight =checkLeftRightShapes(shape0Name,shape2Name);
        bool anyTwoMatchUpInScreenArea=checkTwoScreenAreaMatch(shape0ScreenArea,shape1ScreenArea,shape2ScreenArea);


        cout <<"("<<shape0Name<<","<<shape0BoxHeight<<","<<shape0BoxWidth<<") ";
        cout <<"("<<shape1Name<<","<<shape1BoxHeight<<","<<shape1BoxWidth<<") ";
        cout <<"("<<shape2Name<<","<<shape2BoxHeight<<","<<shape2BoxWidth<<")"<< endl;

        int tokenWon;

        if((countOfSimilarShapes==2 || countOfSimilarShapes==3) && anyTwoMatchUpInScreenArea){
             //Please Note : The condition was understood ,by me,as any two shapes and any 2 match up in screen area
             // this interpretation is realized based on professor email comment to me "Imagine three same shapes
             // and of the same size." . Also not necessary for just same shape to match up in the Screen Area.
            tokenWon = 3 * userBet;
            cout << "Jackpot! 2 Similar Shapes AND 2 Equal Screen Areas" << endl;
            cout << "Congratulations! you win 3 times your bet: "<< tokenWon << endl;
        }
         else if(countOfSimilarShapes==3){
            tokenWon= 2 *userBet;
            cout << "Three similar shapes"<< endl;
            cout << "Congratulations! you win 2 times your bet: "<< tokenWon << endl;
        }
        else if(screenAreaMiddle){
            tokenWon = 1 * userBet;
            cout << "Middle > Left + Right , in Screen Areas" << endl;
            cout << "Congratulations! you win your bet: "<< tokenWon << endl;
        }
        else if (leftSimilarRight){
            tokenWon= 0 * userBet;
            cout << "Lucky this time!" << endl;
            cout << "You don't win,you don't lose, you are safe!" << endl;
        }
        else {
            tokenWon= -1 * userBet;
            cout << "Oh No!"<< endl;
            cout << "You loose your bet" << endl;
        }

        slotTokens+=tokenWon;//Step 20 : Update the slotToken using prize payout
        cout << "You now have "<< slotTokens << " tokens"<< endl;  //Step 21: Displaying whether the player has won,lost, or neither

        if(slotTokens==0){ // Check if after updating token slot the remaining slots is greater than 0 otherwise quit
            break;
        }
    }

    cout << "Thank you for playing,come back soon!" << endl;
    if(slotTokens >0){
        cout << "Be sure you cash in your remaining " << slotTokens << " tokens at the bar!"<< endl;
    }
    else{
        cout << "No slot Token remaining!" << endl;
    }
    cout << "Game Over." << endl;

}

