#include <string.h>
#include <list>
#include <vector>
#include <iterator>
using std::string;
using std::list;
using std::vector;
/**
	Assignment 1, LineEd.h
	Purpose: Class LineEd is a line editor
	@author Simran Sidhu
*/
class LineEd{
    private:
		list<string> buffer; // Holds the content of an existing file and current updates made by the user in an editing session
        vector<string> clipBoard; // Temporary placeHolder used in an editing session
        int currentLine; // Current line
        string filename; // File being edited
        void validateLineAddress(string &); // Validate a parsed line address
        void validateLineAddresses(string &,string &); // Validate parsed line address1 and line address2
        string fileStatus;//Any changes in an editing session - this is set to updated
    public:
        LineEd (const string & fileName); //Constructor to initiate an editor on a file
        void runCommand(const string & command); //Performs Single Command to a file
        void run(); // Provides user with a continuous editing session till command q is pressed
};
