#include <string>
using std::string;
/**
	Assignment 1, Command.h
	Purpose: Command class is used to parse a command line into command symbol and line address1 and line address2.
	@author Simran Sidhu
*/
class Command{
    private:
        string command_line;//Stores the supplied command line
        bool status;//stores validity of command line
        string symbol;//stores the command symbol
        string address1;//stores line address 1
        string address2;//stores line address2
        string status_msg;// stores any command failure messages
        void fetchSymbolAddress1(string &);//extracts symbol and line address1 from command line
        void fetchAddress2(string &);//extracts line address2 from command line
    public:
        Command (const string & commandline); //constructor,set and parse command line
        void parse(const string & commandline); //Resets and parses command line
        void setStatusMsg(const string & statusMsg); //Sets the reason of a invalid parsed command line
        void setStatus(bool status);//set the validity status of the command line
        string getSymbol();//Return command symbol
        string getAddress1(); //Return line address1
        string getAddress2();// Return line address2
        bool getStatus(); // Return the validity status of a command line
        string getStatusMsg(); //Return command failure message - used in case a command line is parsed and found invalid

};
