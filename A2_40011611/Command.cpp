#include <iostream>
#include <cctype>
#include <ctype.h> //for removing space
#include <vector>
#include "Command.h"
using std::cout;
using std::endl;
using std::vector;
/**
	Assignment 1, Command.cpp
	Purpose: Command class is used to parse a command line into command symbol and line address1 and line address2.
             Command.cpp is an implementation of command.h header file
	@author Simran Sidhu
*/

/*
Constructor set and parse command line
@ commandline constant reference to a string holding the command line entered by user
*/
Command::Command(const string& commandline) {
    //Default initialization of the data members
	this->symbol = "p";
	this->address1=".";
	this->address2=address1;
	this->status=true;//validity status
	this->status_msg="none";
	parse(commandline);
}

/*
Extracts symbol and line address1 from command line
@ command a string holding the symbol and line address1
*/
void Command::fetchSymbolAddress1(string & command){

    string numberic{"0123456789.$-"};
    std::size_t foundNumPos = command.find_first_of(numberic);
    if(foundNumPos!=std::string::npos){ //Numbers exists
        if(foundNumPos==0){ //No symbol supplied
            this->address1=command.substr(foundNumPos);
        }
        else if (foundNumPos>0){
            this->symbol=command.substr(0,foundNumPos);
            if(symbol.size()==1) { //Only 1 command symbol allowed
                this->address1= command.substr(foundNumPos);
            }else{
                this->status=false;
                this->status_msg="Bad Command: Incorrect command symbol";
                this->symbol="";
                this->address1="";
            }
        }
    }
     else{ //No Numbers existing
            if(!command.empty()){
                this->symbol=command;
            }

            if(symbol.size()>1) {
                this->status=false;
                this->status_msg="Bad Command: Incorrect command symbol";
                this->symbol="";
                this->address1="";
            }
    }
}

/*
Extracts line address2 from command line
@ command a string holding the line address2
*/
void Command::fetchAddress2(string & command){
    if(!command.empty()){
        this->address2=command;
        return;
    }
    this->address2=address1;
}

/*
Resets and parses command line
@ commandline constant reference to a string holding the command line entered by user
*/
void Command::parse(const string & commandline){
    string cmd;
    for(char ch : commandline){ //Removing whitespace
        if (!isspace(ch)){
            cmd+=ch;
        }
    }
    this->command_line = cmd;
    //cout << " command_line:" << command_line<<" "<<command_line.empty() <<" " << command_line.size() << endl;

    //Vector holding the three components of a command line
    vector<string>commandHolder; // this vector is empty if no character is entered
    if(!command_line.empty()){
        //cout << "first character is :" << command_line.at(0) << endl;
        if(command_line.at(0)==','){
            //checking if the first character is comma - prepend p. as the symbol and first address1 are missing
            command_line="p."+command_line;
        }
     //-----------------Split the string by comma...!-
     string delimiter(",");
     std::size_t currPos=0;
     std::size_t foundPos = command_line.find(delimiter);
     while (foundPos!=std::string::npos){
          int lengthSubStr= foundPos-currPos;
          commandHolder.push_back(command_line.substr(currPos, lengthSubStr));
          foundPos++;
          currPos=foundPos;
          foundPos = command_line.find(delimiter,foundPos);
       }
         commandHolder.push_back(command_line.substr(currPos));
    }

    //EXTRACTING SYMBOL,ADDRESS1,ADDRESS2
    if(commandHolder.size()==1){ //Updates to the symbol and address1
        fetchSymbolAddress1(commandHolder[0]);
        this->address2=address1;
    }
    else if(commandHolder.size()==2){ //Updates to the symbol , address1 ,address2
        //cout << "2 ele Vector..!" << endl;
        fetchSymbolAddress1(commandHolder[0]);
        fetchAddress2(commandHolder[1]);

    }else if (commandHolder.size()>2){
        //Not a Valid command..
        cout << "This is error!" << endl;
        this->status=false;//false means the command_line is invalid
        this-> status_msg="Bad Command : More than two line address supplied";
        this-> symbol="";
        this->address1="";
        this->address2="";
    }
}

/*
Return command symbol
@return (string)symbol
*/
string Command::getSymbol(){
    return symbol;
}

/*
Return line address1
@return (string) line address1
*/
string Command::getAddress1(){
    return address1;
}

/*
Return line address2
@return (string) line address2
*/
string Command::getAddress2(){
    return address2;
}

/*
Return validity status of the command line entered by user
@return (bool) validity status
*/
bool Command::getStatus(){
    return status;
}

/*
Return validity status's message i.e. invalid reason of the parsed command line entered by user
@return (string) validity status message
*/
string Command::getStatusMsg(){
    return status_msg;
}
/*
Set the validity status of the command line
@status validity status of the command line parsed
*/
void Command::setStatus(bool status){
    this-> status = status;
}

/*
Sets the reason of a invalid parsed command line
@statusMsg constant reference to a string holding the invalid reason of parsed command line
*/
void Command::setStatusMsg(const string & statusMsg){
    this->status_msg=statusMsg;
}
