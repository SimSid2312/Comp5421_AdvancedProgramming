#include<iostream>
#include <fstream>
#include <string.h>
#include <list>
#include <vector>
#include <iterator>
#include "LineEd.h"
#include "Command.h"
using std::cout;
using std::cin;
using std::endl;
using std::string;
using std::list;
using std::vector;
using std::ifstream;
using std::ofstream;
using std::to_string;
using std::stoi;
using std::skipws;
/**
	Assignment 1, LineEd.cpp
	Purpose: Class LineEd is a line editor.
             LineEd.cpp is implementation of LineEd.h headerfile
	@author Simran Sidhu
*/

/*
Constructor to initiate an editor on a file
@ fileName constant reference to a string holding the name of the file
*/
LineEd::LineEd(const string & fileName) {
    //default setup of the data members
    ifstream fin;
    fin.open(fileName);
    if(!fin) { //Shows file cannot be open
		cout << "Cannot open file: " << endl;
        filename=fileName; 
        this->clipBoard.clear();
        this->buffer.clear();
        currentLine=0;

    }else{ //File exists and we need to populate the buffer
        currentLine=0;
        filename=fileName;
        this->clipBoard.clear();
        string line;
        while(getline(fin,line)){
            this->buffer.push_back(line);
            currentLine++;
        }      

    }
}

/*
Validate parsed line address1 and line address2
@ address1 constant reference to a string line address1,
@ address2 constant reference to a string line address2
*/
void LineEd::validateLineAddresses(string &address1,string &address2){

    if(address1==".")    {
        address1 = to_string(currentLine);
    }
    if(address1=="$")    {
        address1 = to_string(buffer.size());
    }
     if(address2==".")    {
        address2 = to_string(currentLine);
    }
    if(address2=="$")    {
        address2 = to_string(buffer.size());
    }


    if(stoi(address1) < 0) {
        address1=to_string(1);
    }else if(stoi(address1)>buffer.size()) {
        address1=to_string(buffer.size());
    }

     if(stoi(address2) < 0){
        address2=to_string(1);
    }else if(stoi(address2)>buffer.size()){
        address2=to_string(buffer.size());        
    }

    if(stoi(address1) > stoi(address2)){
        string temp=address1;
        address1=address2;
        address2=temp;
    }
}


/*
Validate a parsed line address
@ address constant reference to a string line address
*/
void LineEd::validateLineAddress(string & address){
     if(address==".")    {
        address = to_string(currentLine);
    }
    if(address=="$")    {
        address = to_string(buffer.size());
    }

    if(stoi(address) < 0) {
        address=to_string(1);
    }else if(stoi(address)>buffer.size()) {
        address=to_string(buffer.size());
    }

}


/*
Provides user with a continuous editing session till command q is pressed
*/
void LineEd::run() {
    if(filename.empty()&&buffer.size()==0){ //no name editor
        cout << "\"" << "?" << "\"" << " [New File]" << endl;
    }else if ((!filename.empty()) && buffer.size()==0){ // non existing file editor
        cout << "\"" << filename << "\"" << " [New File]" << endl;
    }
    else { //existing file editor
        cout  << "\"" << filename << "\"" << " " << buffer.size() << " lines" << endl;

    }
    cout << "Entering into Command mode." << endl;
    int flag=0;
      while(flag==0){
        cin.clear();
        cout << "?";
        string userInputCmd;
        getline(cin, userInputCmd);
        Command cmd(userInputCmd);
        if(cmd.getStatus()){
           string symb; //Making the command symbol case insensitive
           for (char ch:cmd.getSymbol()){
            symb+=toupper(ch);
        }
        switch(symb.at(0)){
             case 'I' : {

                            cout << "\nEntering input mode." << endl;
                            if(buffer.size()==0){
                                string userInputText;
                                while (getline(cin, userInputText))
                                {   if(userInputText=="."){
                                    cout << "Entering command mode." << endl;
                                    break;
                                }
                                buffer.push_back(userInputText);
                                ++currentLine;
                                }
                                fileStatus="updated";
                            }
                            else{
                                 string addr1= cmd.getAddress1();
                                 std::size_t foundAddr1 = addr1.find_first_of("$.");
                                 if(foundAddr1!=std::string::npos && addr1.size()>1){
                                    cout << "Bad address 1 :" << addr1 << endl;                                    
                                    cmd.setStatus(false);
                                    cmd.setStatusMsg("Bad address 1 :"+addr1);                                   
                                    break;
                                }
                                string numberic{"0123456789.$-"}; //Checking for non-numeric character
                                std::size_t foundNonNumInAddr1 = addr1.find_first_not_of(numberic);
                                if(foundNonNumInAddr1!=std::string::npos){
                                    cout << "Bad Address 1: " << addr1 << endl;                                     
                                    cmd.setStatus(false);
                                    cmd.setStatusMsg("Bad address 1 :"+addr1);                                  

                                }else {
                                    fileStatus="updated";
                                    int elementNum=1;
                                    validateLineAddress(addr1);
                                    list<string>::iterator bufferItr=buffer.begin();
                                    int loopTerminator=1;
                                    while(loopTerminator){
                                         if(elementNum==stoi(addr1)){
                                            string userInputText;
                                            std::vector<string> myvector;
                                            while (getline(cin, userInputText)){
                                                if(userInputText=="."){
                                                    buffer.insert (bufferItr,myvector.begin(),myvector.end());
                                                        currentLine=(elementNum-1)+myvector.size();
                                                    cout << "Entering command mode." << endl;
                                                    loopTerminator=0;
                                                    break;
                                                }
                                                myvector.push_back(userInputText);                                           
											}
                                         }
                                        ++bufferItr;
                                        ++elementNum;
                                    }
                                }
                            }
                        }
                        break;

             case 'A' : {   fileStatus="updated";
                            cout << "\nEntering input mode." << endl;
                            string userInputText;
                            while (getline(cin, userInputText))
                            {   if(userInputText=="."){
                                cout << "Entering command mode." << endl;
                                break;
                                }
                                buffer.push_back(userInputText);
                            }
                            currentLine=buffer.size();
                        }
                        break;

             case 'P' : {
                          if(buffer.size()==0){
                             cout << "File empty.Must use one of I,A,Q commands." << endl;
                          }
                          else{
                             string addr1= cmd.getAddress1();
                             string addr2=cmd.getAddress2();           
                             std::size_t foundAddr1 = addr1.find_first_of("$.");
                             std::size_t foundAddr2 = addr2.find_first_of("$.");
                             if(foundAddr1!=std::string::npos && addr1.size()>1){
                                cout << "Bad address 1 :" << addr1 << endl;                              
                                cmd.setStatus(false);
                                cmd.setStatusMsg("Bad address 1 :"+addr1);                              
                                break;
                             }
                             if(foundAddr2!=std::string::npos && addr2.size()>1){
                                cout << "Bad address 2 :" << addr2 << endl;                            
                                cmd.setStatus(false);
                                cmd.setStatusMsg("Bad address 2 :"+addr2);                                  
                                break;
                             }

                             string numberic{"0123456789.$-"}; //Checking for non-numeric character
                             std::size_t foundNonNumInAddr1 = addr1.find_first_not_of(numberic);
                             std::size_t foundNonNumInAddr2 = addr2.find_first_not_of(numberic);
                             if(foundNonNumInAddr1!=std::string::npos){
                                cout << "Bad Address 1: " << addr1 << endl;                                
                                cmd.setStatus(false);
                                cmd.setStatusMsg("Bad address 1 :"+addr1);
                                    
                             }
                             else if (foundNonNumInAddr2!=std::string::npos){
                                cout << "Bad Address 2: " << addr2 << endl;
                                cmd.setStatus(false);
                                cmd.setStatusMsg("Bad address 2 :"+addr2);                                  

                             }
                             else {
                                 validateLineAddresses(addr1,addr2);
                                 int elementNum=1;
                                 list<string>::iterator bufferItr=buffer.begin();
                                 for(;bufferItr!=buffer.end();bufferItr++){
                                    if(elementNum>=stoi(addr1) && elementNum <=stoi(addr2)){
                                            if(elementNum==currentLine){
                                                cout << elementNum << ">" << *bufferItr<< endl;
                                            }
                                            else{
                                                cout << elementNum << ":" << *bufferItr<< endl;
                                            }
                                            elementNum++;
                                    }
                                    else{
                                     elementNum++;
                                    }
                                 }//End of for loop!
                              }
                           }
                        }
                        break;

             case 'Q' : {
                            if(fileStatus=="updated"){
                                cout << "There is unsaved changed." << endl;
                                string userResponse;
                                string ch;
                                do{
                                    cout << "Do you wish to save the changes (y or n)? ";
                                    cin>>skipws;
                                    getline(cin,userResponse);                     
                                    ch = tolower(userResponse.at(0));  
                                    }while(ch!="y" && ch!="n");

                                 if(ch=="y"){
                                    if(filename.empty()){
                                        cout << "Enter the filename to write to : ";
                                        string fname;
                                        cin>>skipws;
                                        getline(cin,fname);
                                        filename=fname;
                                    }else if (!filename.empty()){
                                        string filenameRes;
                                        string chRes;
                                        int doWhileItr=0;
                                        do{
                                            if(doWhileItr!=0){
                                                cout << "Enter the name of the file to write to: ";
                                                string fname;
                                                cin>>skipws;
                                                getline(cin,fname);
                                                filename=fname;
                                            }
                                            cout << "Save changes to file : " << filename << " (y)?";
                                            cin>>skipws;
                                            getline(cin,filenameRes);
                                            chRes = tolower(filenameRes[0]);
                                            doWhileItr++;
                                        }while(chRes!="y");

                                    }

                                     ofstream fout;
                                     fout.open(filename);
                                     list<string>::iterator bufferItr=buffer.begin();
                                     for(;bufferItr!=buffer.end();bufferItr++){
                                        fout << *bufferItr << endl;
                                     }
                                     fout.close();
                                     cout << buffer.size() << " lines written to file "<< "\""<< filename << "\""<< endl;
                                     cout << "bye" << endl;
                                     flag=1;

                            }else{ // User is not willing to save the change - simply quit
                                 cout << "Changes unsaved, bye" << endl;
                                 buffer.clear();
                                 clipBoard.clear();
                                 flag=1; // Exiting out flag
                            }
                         }
                         else { //User made no changes in the editing session
                            cout << "No unsaved changes ,bye" << endl;
                            flag=1; // Exiting out flag
                            }
                        }
                        break;

            case 'W'  : {
                           if(fileStatus=="updated"){
                            if(filename.empty()){
                                cout << "Enter the filename to write to : ";
                                string fname;
                                cin>>skipws;
                                getline(cin,fname);
                                filename=fname;
                            }else if (!filename.empty()){
                                string filenameRes;
                                string chRes;
                                int doWhileItr=0;
                                do{
                                    if(doWhileItr!=0){
                                    cout << "Enter the name of the file to write to: ";
                                     string fname;
                                     cin>>skipws;
                                     getline(cin,fname);
                                     filename=fname;
                                     }
                                     cout << "Save changes to file : " << filename << " (y)?";
                                     cin>>skipws;
                                     getline(cin,filenameRes);
                                     chRes = tolower(filenameRes[0]);
                                     doWhileItr++;

                                    }while(chRes!="y");
                                }
                                ofstream fout;
                                fout.open(filename);
                                list<string>::iterator bufferItr=buffer.begin();
                                for(;bufferItr!=buffer.end();bufferItr++){
                                     fout << *bufferItr << endl;
                                }
                                fout.close();
                                cout << buffer.size() << " lines written to file "<< "\""<< filename << "\""<< endl;
                                fileStatus="";//setting this ensure that the user is not asked for saving again upon pressing q
                           }
                           else{
                               cout << "No unsaved changes so far." << endl;
                           }
                        }
                        break;
            case 'G' : {
                            string addr1=cmd.getAddress1();
                            std::size_t foundAddr1 = addr1.find_first_of("$.");

                            if(foundAddr1!=std::string::npos && addr1.size()>1){
                                cout << "Bad address 1 :" << addr1 << endl;                            
                                cmd.setStatus(false);
                                cmd.setStatusMsg("Bad address 1 :"+addr1);                                  
                                break;
                            }
                            string numberic{"0123456789.$-"}; //Checking for non-numeric character
                            std::size_t foundNonNumInAddr1 = addr1.find_first_not_of(numberic);
                            if(foundNonNumInAddr1!=std::string::npos){
                                cout << "Bad Address 1: " << addr1 << endl;                              
                                cmd.setStatus(false);
                                cmd.setStatusMsg("Bad address 1 :"+addr1);
                                  
                            }else {
                                 validateLineAddress(addr1);
                                 int elementNum=1;
                                 currentLine=stoi(addr1); // go to that line
                                  //Print that the line
                                 list<string>::iterator bufferItr=buffer.begin();
                                 for(;bufferItr!=buffer.end();bufferItr++){
                                    if(elementNum==currentLine){
                                        cout << elementNum << ">" << *bufferItr<< endl;
                                     }
                                     elementNum++;
                                 }
                              }

                        }
                        break;

            case 'D' : {   //Validation checks on addr1 and addr2
                            string addr1= cmd.getAddress1();
                            string addr2=cmd.getAddress2();   
                            std::size_t foundAddr1 = addr1.find_first_of("$.");
                            std::size_t foundAddr2 = addr2.find_first_of("$.");
                             if(foundAddr1!=std::string::npos && addr1.size()>1){
                                cout << "Bad address 1 :" << addr1 << endl;                             
                                    cmd.setStatus(false);
                                    cmd.setStatusMsg("Bad address 1 :"+addr1);                                 
                                break;
                             }
                             if(foundAddr2!=std::string::npos && addr2.size()>1){
                                cout << "Bad address 2 :" << addr2 << endl;                               
                                    cmd.setStatus(false);
                                    cmd.setStatusMsg("Bad address 2 :"+addr2);                               
                                break;
                             }
                             string numberic{"0123456789.$-"}; //Checking for non-numeric character
                             std::size_t foundNonNumInAddr1 = addr1.find_first_not_of(numberic);
                             std::size_t foundNonNumInAddr2 = addr2.find_first_not_of(numberic);
                             if(foundNonNumInAddr1!=std::string::npos){
                                cout << "Bad Address 1: " << addr1 << endl;                              
                                cmd.setStatus(false);
                                cmd.setStatusMsg("Bad address 1 :"+addr1);
                                    
                             }
                             else if (foundNonNumInAddr2!=std::string::npos){
                                cout << "Bad Address 2: " << addr2 << endl;                               
                                cmd.setStatus(false);
                                cmd.setStatusMsg("Bad address 2 :"+addr2);
                                   
                             }else {
                                 validateLineAddresses(addr1,addr2);
                                 //deletion code
                                std::list<string>::iterator range_begin = buffer.begin();
                                std::list<string>::iterator range_end = buffer.begin();
                                std::advance(range_begin, (stoi(addr1) -1));
                                std::advance(range_end,stoi(addr2)); // not making -1 to make range_end inclusive in erase                   
                                int addr1_index =std::distance(buffer.begin(),range_begin);
                                int addr2_index=std::distance(buffer.begin(),range_end)-1;                                
                                if(addr2_index !=buffer.size()-1){                                   
                                     buffer.erase (range_begin,range_end);                                     
                                     currentLine=(std::distance(buffer.begin(),range_end))+1;                        

                                }else if (addr1_index != 0 ){                          
                                    buffer.erase (range_begin,range_end);                                
                                    currentLine=addr1_index;                   

                                }else{
                                    buffer.erase (range_begin,range_end);
                                    buffer.clear();
                                    currentLine=0;
                                }
                                fileStatus="updated"; // user made edit in this session
                            
                             }

                       }
                        break;

            case 'X' :{
                            string addr1= cmd.getAddress1();
                            string addr2=cmd.getAddress2();                         
                            std::size_t foundAddr1 = addr1.find_first_of("$.");
                            std::size_t foundAddr2 = addr2.find_first_of("$.");
                             if(foundAddr1!=std::string::npos && addr1.size()>1){
                                cout << "Bad address 1 :" << addr1 << endl;                              
                                    cmd.setStatus(false);
                                    cmd.setStatusMsg("Bad address 1 :"+addr1);                                   
                                break;
                             }
                             if(foundAddr2!=std::string::npos && addr2.size()>1){
                                cout << "Bad address 2 :" << addr2 << endl;                             
                                    cmd.setStatus(false);
                                    cmd.setStatusMsg("Bad address 2 :"+addr2);                                 
                                break;
                             }
                             string numberic{"0123456789.$-"}; //Checking for non-numeric character
                             std::size_t foundNonNumInAddr1 = addr1.find_first_not_of(numberic);
                             std::size_t foundNonNumInAddr2 = addr2.find_first_not_of(numberic);
                             if(foundNonNumInAddr1!=std::string::npos){
                                cout << "Bad Address 1: " << addr1 << endl;                               
                                    cmd.setStatus(false);
                                    cmd.setStatusMsg("Bad address 1 :"+addr1);                                 
                             }
                             else if (foundNonNumInAddr2!=std::string::npos){
                                cout << "Bad Address 2: " << addr2 << endl;                             
                                    cmd.setStatus(false);
                                    cmd.setStatusMsg("Bad address 2 :"+addr2);                                  
                             }
                             else{
                                validateLineAddresses(addr1,addr2);
                                //Populate the clipBoard
                                std::list<string>::iterator range_begin = buffer.begin();
                                std::list<string>::iterator range_end = buffer.begin();
                                std::advance(range_begin, (stoi(addr1) -1));
                                std::advance(range_end,stoi(addr2));                             
                               
                                std::list<string>::iterator range_ClipBoard = range_begin;
                               for(;range_ClipBoard!=range_end && range_ClipBoard!=buffer.end() ;++range_ClipBoard){
                                     clipBoard.push_back(*range_ClipBoard);
                                }

                                //delete the element from buffer.
                                int addr1_index =std::distance(buffer.begin(),range_begin);
                                int addr2_index=std::distance(buffer.begin(),range_end)-1;                            
                                if(addr2_index !=buffer.size()-1){                                   
                                     buffer.erase (range_begin,range_end);
                                     currentLine=(std::distance(buffer.begin(),range_end))+1;                                     

                                }else if (addr1_index != 0 ){   
                        
                                    buffer.erase (range_begin,range_end);
                          
                                    currentLine=addr1_index;
                             

                                }else{
                                    buffer.erase (range_begin,range_end);
                                    buffer.clear();
                                    currentLine=0;
                                }
                                fileStatus="updated"; // user made edit in this session
                               


                             }

                      }
                      break;

            case 'J' :{
                        //Validation checks on addr1 and addr2
                        string addr1= cmd.getAddress1();
                        string addr2=cmd.getAddress2();
                      
                     
                    
                        std::size_t foundAddr1 = addr1.find_first_of("$.");
                        std::size_t foundAddr2 = addr2.find_first_of("$.");
                        if(foundAddr1!=std::string::npos && addr1.size()>1){
                              cout << "Bad address 1 :" << addr1 << endl;
                               
                             cmd.setStatus(false);
                              cmd.setStatusMsg("Bad address 1 :"+addr1);
                                  
                                break;
                        }
                        if(foundAddr2!=std::string::npos && addr2.size()>1){
                                cout << "Bad address 2 :" << addr2 << endl;
                                
                                cmd.setStatus(false);
                                cmd.setStatusMsg("Bad address 2 :"+addr2);
                                    
                                break;
                        }
                        string numberic{"0123456789.$-"}; //Checking for non-numeric character
                        std::size_t foundNonNumInAddr1 = addr1.find_first_not_of(numberic);
                        std::size_t foundNonNumInAddr2 = addr2.find_first_not_of(numberic);
                        if(foundNonNumInAddr1!=std::string::npos){
                            cout << "Bad Address 1: " << addr1 << endl;
                            
                                    cmd.setStatus(false);
                                    cmd.setStatusMsg("Bad address 1 :"+addr1);
                                 
                        }
                        else if (foundNonNumInAddr2!=std::string::npos){
                                cout << "Bad Address 2: " << addr2 << endl;
                                
                                    cmd.setStatus(false);
                                    cmd.setStatusMsg("Bad address 2 :"+addr2);
                                    
                        }else{
                             validateLineAddresses(addr1,addr2);
                             std::list<string>::iterator range_begin = buffer.begin();
                             std::list<string>::iterator range_end = buffer.begin();
                             std::advance(range_begin, (stoi(addr1) -1));
                             std::advance(range_end,stoi(addr2)); // not making -1 to make range_end inclusive
                         
                            
                           
                             std::list<string>::iterator join_itr=range_begin;
                             string joinPlaceHolder;
                             for(;join_itr!=range_end;++join_itr){
                                    joinPlaceHolder+=*join_itr;
                             }
                             
                             //replace
                             *range_begin=joinPlaceHolder;
                             currentLine=std::distance(buffer.begin(),range_begin)+1;
                            
                             //deletion code - increment by 1 index the range_begin
                             ++range_begin;
                            int addr1_index =std::distance(buffer.begin(),range_begin);
                            int addr2_index=std::distance(buffer.begin(),range_end)-1;
                           
                      
                            buffer.erase (range_begin,range_end);
                            fileStatus="updated";
                        }

                      }
                      break;

            case 'C' : {
                         //Validation checks on addr1 and addr2
                         string addr1= cmd.getAddress1();
                         string addr2=cmd.getAddress2();
                     
                     
                      
                         std::size_t foundAddr1 = addr1.find_first_of("$.");
                         std::size_t foundAddr2 = addr2.find_first_of("$.");
                         if(foundAddr1!=std::string::npos && addr1.size()>1){
                                cout << "Bad address 1 :" << addr1 << endl;
                               
                                    cmd.setStatus(false);
                                    cmd.setStatusMsg("Bad address 1 :"+addr1);
                                  
                                break;
                          }
                         if(foundAddr2!=std::string::npos && addr2.size()>1){
                                cout << "Bad address 2 :" << addr2 << endl;
                                
                                    cmd.setStatus(false);
                                    cmd.setStatusMsg("Bad address 2 :"+addr2);
                                    
                                break;
                         }
                         string numberic{"0123456789.$-"}; //Checking for non-numeric character
                         std::size_t foundNonNumInAddr1 = addr1.find_first_not_of(numberic);
                         std::size_t foundNonNumInAddr2 = addr2.find_first_not_of(numberic);
                         if(foundNonNumInAddr1!=std::string::npos){
                                cout << "Bad Address 1: " << addr1 << endl;
                                
                                    cmd.setStatus(false);
                                    cmd.setStatusMsg("Bad address 1 :"+addr1);
                                   
                         }
                          else if (foundNonNumInAddr2!=std::string::npos){
                                cout << "Bad Address 2: " << addr2 << endl;
                                
                                    cmd.setStatus(false);
                                    cmd.setStatusMsg("Bad address 2 :"+addr2);
                                    
                          }else {
                             validateLineAddresses(addr1,addr2);
                             cout << "change ? ";
                             string oldText;
                             //cin>>skipws;
                             getline(cin,oldText);
                         
                             cout << "to ? ";
                             string updatedText;
                             //cin>>skipws;
                             getline(cin,updatedText);
                           
                             std::list<string>::iterator range_begin = buffer.begin();
                             std::list<string>::iterator range_end = buffer.begin();
                             std::advance(range_begin, (stoi(addr1) -1));
                             std::advance(range_end,stoi(addr2)); // not making -1 to make range_end inclusive in erase
                          
                           
                             for(;range_begin!=range_end;++range_begin){
                                string strToUpdate= *range_begin;                               
                              
                                std::size_t found = strToUpdate.find(oldText);
                                if(found!=std::string::npos){//Atleast one change is made.
                                    currentLine=std::distance(buffer.begin(),range_begin)+1;
                                }
                                while(found!=std::string::npos){
                                 
                                    strToUpdate.replace(found,oldText.size(),updatedText);
                                    if(found+1>buffer.size()) break;
                                    found=strToUpdate.find(oldText,found+oldText.size());
                                }
                            
                                *range_begin=strToUpdate;
                             }
                           


                             fileStatus="updated"; // user made edit in this session
                        

                          }


                       }
                       break;

            case 'V' :{
                            string addr1= cmd.getAddress1();
                            string addr2= cmd.getAddress2();
                            bool addr2Usable=true; // to make ("v100,1") to work!
                            std::size_t foundAddr1 = addr1.find_first_of("$.");
                            std::size_t foundAddr2 = addr2.find_first_of("$.");
                            if(foundAddr1!=std::string::npos && addr1.size()>1){
                                    cout << "Bad address 1 :" << addr1 << endl;
                                   
                                    cmd.setStatus(false);
                                    cmd.setStatusMsg("Bad address 1 :"+addr1);
                                   
                                    break;
                            }
                            if(foundAddr2!=std::string::npos && addr2.size()>1){

                                addr2Usable=false;

                             }

                             string numberic{"0123456789.$-"}; //Checking for non-numeric character
                             std::size_t foundNonNumInAddr1 = addr1.find_first_not_of(numberic);
                             std::size_t foundNonNumInAddr2 = addr2.find_first_not_of(numberic);
                             if (foundNonNumInAddr2!=std::string::npos){

                                 addr2Usable=false;
                              }
                               if(foundNonNumInAddr1!=std::string::npos){
                                    cout << "Bad Address 1: " << addr1 << endl;
                                    
                                    cmd.setStatus(false);
                                    cmd.setStatusMsg("Bad address 1 :"+addr1);
                                   
                            }else {
                                    validateLineAddress(addr1);
                                    if(addr2Usable){
                                        validateLineAddresses(addr1,addr2);
                                    }                             


                                    std::list<string>::iterator range_begin = buffer.begin();
									if (stoi(addr1) == 0) {
										std::advance(range_begin, stoi(addr1));
									}
									else {
										std::advance(range_begin, (stoi(addr1) - 1));
									}
                                    if(clipBoard.size()!=0){
                                        std::vector<string>::iterator vectItr=clipBoard.begin();
                                        for(;vectItr!=clipBoard.end();++vectItr){
                                            buffer.insert(range_begin,*vectItr);
                                           
                                        }
                                        currentLine=std::distance(buffer.begin(),range_begin);//not doing +1
                                    
                                        fileStatus="updated";
                                        clipBoard.clear(); // empty the clipBoard
                                    }else{
                                        cout <<"ClipBoard empty , no paste" << endl;
                                    }
                            }
                      }
                      break;

            case 'U' :{
                            if(currentLine-1 == 0){
                                currentLine=1;
                                cout<<"BOF reached"<<endl;
                            }
                            else{
                                --currentLine;
                                int elementNum=1;
                            list<string>::iterator bufferItr=buffer.begin();
                            for(;bufferItr!=buffer.end();bufferItr++){
                                if(elementNum==currentLine){
                                       cout << currentLine << ">" << *bufferItr<< endl;
                                }
                                    elementNum++;
                                }//End of for loop!
                          }
                      }
                       break;
            case 'N' :{
                        if(currentLine == buffer.size()){
                            currentLine=buffer.size();
                            cout<<"EOF reached"<<endl;
                        }else{
                            ++currentLine;
                            int elementNum=1;
                            list<string>::iterator bufferItr=buffer.begin();
                            for(;bufferItr!=buffer.end();bufferItr++){
                              if(elementNum==currentLine){
                                cout << currentLine << ">" << *bufferItr<< endl;
                            }
                             elementNum++;
                            }//End of for loop!
                        }


                      }
                      break;
            default:
                        cout << "Bad Command :" << cmd.getSymbol() << endl;

            } // end of switch
        } // end of if
        else {
            cout << cmd.getStatusMsg() << endl;
        } // endl of else

    } // end of while

}

/*
Performs Single Command to a file
@command constant reference to a string holding the command line entered by user
*/
void LineEd::runCommand(const string & command){
    cout << "Entering into Command mode." << endl;
    Command cmd(command);
     if(cmd.getStatus()){
           string symb; //Making the command symbol case insensitive
           for (char ch:cmd.getSymbol()){
            symb+=toupper(ch);
        }
        switch(symb.at(0)){
             case 'I' : {
                            cout << "\nEntering input mode." << endl;
                            if(buffer.size()==0){
                                string userInputText;
                                while (getline(cin, userInputText))
                                {   if(userInputText=="."){
                                    cout << "Entering command mode." << endl;
                                    break;
                                }
                                buffer.push_back(userInputText);
                                ++currentLine;
                                }
                                fileStatus="updated";
                            }
                            else{
                                 string addr1= cmd.getAddress1();
                                 std::size_t foundAddr1 = addr1.find_first_of("$.");
                                 if(foundAddr1!=std::string::npos && addr1.size()>1){
                                    cout << "Bad address 1 :" << addr1 << endl;
                                   
                                    cmd.setStatus(false);
                                    cmd.setStatusMsg("Bad address 1 :"+addr1);
                                   
                                    break;
                                }
                                string numberic{"0123456789.$-"}; //Checking for non-numeric character
                                std::size_t foundNonNumInAddr1 = addr1.find_first_not_of(numberic);
                                if(foundNonNumInAddr1!=std::string::npos){
                                    cout << "Bad Address 1: " << addr1 << endl;
                                    
                                    cmd.setStatus(false);
                                    cmd.setStatusMsg("Bad address 1 :"+addr1);
                                   

                                }else {
                                    fileStatus="updated";
                                    int elementNum=1;
                                    validateLineAddress(addr1);
                                    list<string>::iterator bufferItr=buffer.begin();
                                    int loopTerminator=1;
                                    while(loopTerminator){
                                         if(elementNum==stoi(addr1)){
                                            string userInputText;
                                            std::vector<string> myvector;
                                            while (getline(cin, userInputText)){
                                                if(userInputText=="."){
                                                    buffer.insert (bufferItr,myvector.begin(),myvector.end());

                                                        currentLine=(elementNum-1)+myvector.size();

                                                    cout << "Entering command mode." << endl;
                                                    loopTerminator=0;
                                                    break;
                                                }
                                                myvector.push_back(userInputText);                                           }
                                         }
                                        ++bufferItr;
                                        ++elementNum;
                                    }
                                }
                            }
                        }
                        break;

             case 'A' : {   fileStatus="updated";
                            cout << "\nEntering input mode." << endl;
                            string userInputText;
                            while (getline(cin, userInputText))
                            {   if(userInputText=="."){
                                cout << "Entering command mode." << endl;
                                break;
                                }
                                buffer.push_back(userInputText);
                            }
                            currentLine=buffer.size();
                        }
                        break;

             case 'P' : {
                          if(buffer.size()==0){
                             cout << "File empty.Must use one of I,A,Q commands." << endl;
                          }
                          else{
                             string addr1= cmd.getAddress1();
                             string addr2=cmd.getAddress2();                     
                             
                             std::size_t foundAddr1 = addr1.find_first_of("$.");
                             std::size_t foundAddr2 = addr2.find_first_of("$.");
                             if(foundAddr1!=std::string::npos && addr1.size()>1){
                                cout << "Bad address 1 :" << addr1 << endl;
                                
                                    cmd.setStatus(false);
                                    cmd.setStatusMsg("Bad address 1 :"+addr1);
                                    
                                break;
                             }
                             if(foundAddr2!=std::string::npos && addr2.size()>1){
                                cout << "Bad address 2 :" << addr2 << endl;
                                
                                    cmd.setStatus(false);
                                    cmd.setStatusMsg("Bad address 2 :"+addr2);
                                    
                                break;
                             }

                             string numberic{"0123456789.$-"}; //Checking for non-numeric character
                             std::size_t foundNonNumInAddr1 = addr1.find_first_not_of(numberic);
                             std::size_t foundNonNumInAddr2 = addr2.find_first_not_of(numberic);
                             if(foundNonNumInAddr1!=std::string::npos){
                                cout << "Bad Address 1: " << addr1 << endl;
                                
                                    cmd.setStatus(false);
                                    cmd.setStatusMsg("Bad address 1 :"+addr1);
                                   
                             }
                             else if (foundNonNumInAddr2!=std::string::npos){
                                cout << "Bad Address 2: " << addr2 << endl;
                                
                                    cmd.setStatus(false);
                                    cmd.setStatusMsg("Bad address 2 :"+addr2);
                                    
                             }
                             else {
                                 validateLineAddresses(addr1,addr2);
                                 int elementNum=1;
                                 list<string>::iterator bufferItr=buffer.begin();
                                 for(;bufferItr!=buffer.end();bufferItr++){
                                    if(elementNum>=stoi(addr1) && elementNum <=stoi(addr2)){
                                            if(elementNum==currentLine){
                                                cout << elementNum << ">" << *bufferItr<< endl;
                                            }
                                            else{
                                                cout << elementNum << ":" << *bufferItr<< endl;
                                            }
                                            elementNum++;
                                    }
                                    else{
                                     elementNum++;
                                    }
                                 }//End of for loop!
                              }
                           }
                        }
                        break;

             case 'Q' : {
                            if(fileStatus=="updated"){
                                cout << "There is unsaved changed." << endl;
                                string userResponse;
                                string ch;
                                do{
                                    cout << "Do you wish to save the changes (y or n)? ";
                                    cin>>skipws;
                                    getline(cin,userResponse);                                  
                                    ch = tolower(userResponse.at(0));                                
                                  
                                    }while(ch!="y" && ch!="n");

                                 if(ch=="y"){
                                    if(filename.empty()){
                                        cout << "Enter the filename to write to : ";
                                        string fname;
                                        cin>>skipws;
                                        getline(cin,fname);
                                        filename=fname;

                                    }else if (!filename.empty()){
                                        string filenameRes;
                                        string chRes;
                                        int doWhileItr=0;
                                        do{
                                            if(doWhileItr!=0){
                                                cout << "Enter the name of the file to write to: ";
                                                string fname;
                                                cin>>skipws;
                                                getline(cin,fname);
                                                filename=fname;
                                            }
                                            cout << "Save changes to file : " << filename << " (y)?";
                                            cin>>skipws;
                                            getline(cin,filenameRes);
                                            chRes = tolower(filenameRes[0]);
                                            doWhileItr++;

                                        }while(chRes!="y");

                                    }

                                     ofstream fout;
                                     fout.open(filename);
                                     list<string>::iterator bufferItr=buffer.begin();
                                     for(;bufferItr!=buffer.end();bufferItr++){
                                        fout << *bufferItr << endl;
                                     }
                                     fout.close();
                                     cout << buffer.size() << " lines written to file "<< "\""<< filename << "\""<< endl;
                                     cout << "bye" << endl;
                                   

                            }else{ // User is not willing to save the change - simply quit
                                 cout << "Changes unsaved, bye" << endl;
                                 buffer.clear();
                                 clipBoard.clear();
                                
                            }
                         }
                         else { //User made no changes in the editing session
                            cout << "No unsaved changes ,bye" << endl;
                            
                            }
                        }
                        break;

            case 'W'  : {
                           if(fileStatus=="updated"){
                            if(filename.empty()){
                                cout << "Enter the filename to write to : ";
                                string fname;
                                cin>>skipws;
                                getline(cin,fname);
                                filename=fname;
                            }else if (!filename.empty()){
                                string filenameRes;
                                string chRes;
                                int doWhileItr=0;
                                do{
                                    if(doWhileItr!=0){
                                    cout << "Enter the name of the file to write to: ";
                                     string fname;
                                     cin>>skipws;
                                     getline(cin,fname);
                                     filename=fname;
                                     }
                                     cout << "Save changes to file : " << filename << " (y)?";
                                     cin>>skipws;
                                     getline(cin,filenameRes);
                                     chRes = tolower(filenameRes[0]);
                                     doWhileItr++;

                                    }while(chRes!="y");
                                }
                                ofstream fout;
                                fout.open(filename);
                                list<string>::iterator bufferItr=buffer.begin();
                                for(;bufferItr!=buffer.end();bufferItr++){
                                     fout << *bufferItr << endl;
                                }
                                fout.close();
                                cout << buffer.size() << " lines written to file "<< "\""<< filename << "\""<< endl;
                                fileStatus="";//setting this ensure that the user is not asked for saving again upon pressing q
                           }
                           else{
                               cout << "No unsaved changes so far." << endl;
                           }
                        }
                        break;
            case 'G' : {
                            string addr1=cmd.getAddress1();
                            std::size_t foundAddr1 = addr1.find_first_of("$.");

                            if(foundAddr1!=std::string::npos && addr1.size()>1){
                                cout << "Bad address 1 :" << addr1 << endl;
                                 //srs
                                    cmd.setStatus(false);
                                    cmd.setStatusMsg("Bad address 1 :"+addr1);
                                    //---
                                break;
                            }
                            string numberic{"0123456789.$-"}; //Checking for non-numeric character
                            std::size_t foundNonNumInAddr1 = addr1.find_first_not_of(numberic);
                            if(foundNonNumInAddr1!=std::string::npos){
                                cout << "Bad Address 1: " << addr1 << endl;
                                 //srs
                                    cmd.setStatus(false);
                                    cmd.setStatusMsg("Bad address 1 :"+addr1);
                                    //---
                            }else {
                                 validateLineAddress(addr1);
                                 int elementNum=1;
                                 currentLine=stoi(addr1); // go to that line
                                  //Print that the line
                                 list<string>::iterator bufferItr=buffer.begin();
                                 for(;bufferItr!=buffer.end();bufferItr++){
                                    if(elementNum==currentLine){
                                        cout << elementNum << ">" << *bufferItr<< endl;
                                     }
                                     elementNum++;
                                 }
                              }

                        }
                        break;

            case 'D' : {   //Validation checks on addr1 and addr2
                            string addr1= cmd.getAddress1();
                            string addr2=cmd.getAddress2();                           
                          
                            std::size_t foundAddr1 = addr1.find_first_of("$.");
                            std::size_t foundAddr2 = addr2.find_first_of("$.");
                             if(foundAddr1!=std::string::npos && addr1.size()>1){
                                cout << "Bad address 1 :" << addr1 << endl;
                               
                                    cmd.setStatus(false);
                                    cmd.setStatusMsg("Bad address 1 :"+addr1);
                                  
                                break;
                             }
                             if(foundAddr2!=std::string::npos && addr2.size()>1){
                                cout << "Bad address 2 :" << addr2 << endl;
                                
                                    cmd.setStatus(false);
                                    cmd.setStatusMsg("Bad address 2 :"+addr2);
                                   
                                break;
                             }
                             string numberic{"0123456789.$-"}; //Checking for non-numeric character
                             std::size_t foundNonNumInAddr1 = addr1.find_first_not_of(numberic);
                             std::size_t foundNonNumInAddr2 = addr2.find_first_not_of(numberic);
                             if(foundNonNumInAddr1!=std::string::npos){
                                cout << "Bad Address 1: " << addr1 << endl;
                                
                                    cmd.setStatus(false);
                                    cmd.setStatusMsg("Bad address 1 :"+addr1);
                                    
                             }
                             else if (foundNonNumInAddr2!=std::string::npos){
                                cout << "Bad Address 2: " << addr2 << endl;
                                
                                    cmd.setStatus(false);
                                    cmd.setStatusMsg("Bad address 2 :"+addr2);
                                   
                             }else {
                                 validateLineAddresses(addr1,addr2);
                                 //deletion code
                                std::list<string>::iterator range_begin = buffer.begin();
                                std::list<string>::iterator range_end = buffer.begin();
                                std::advance(range_begin, (stoi(addr1) -1));
                                std::advance(range_end,stoi(addr2)); // not making -1 to make range_end inclusive in erase                          
                               
                                int addr1_index =std::distance(buffer.begin(),range_begin);
                                int addr2_index=std::distance(buffer.begin(),range_end)-1;
                                //cout << "addr1_index : " << addr1_index<< endl;
                                //cout << "addr2_index : " << addr2_index<< endl;
                                if(addr2_index !=buffer.size()-1){                                 
                                     buffer.erase (range_begin,range_end);                                 
                                     currentLine=(std::distance(buffer.begin(),range_end))+1;                                  

                                }else if (addr1_index != 0 ){                                      
                                    buffer.erase (range_begin,range_end);                                
                                    currentLine=addr1_index;                                    

                                }else{
                                    buffer.erase (range_begin,range_end);
                                    buffer.clear();
                                    currentLine=0;
                                }
                                fileStatus="updated"; // user made edit in this session
                       
                             }

                       }
                        break;

            case 'X' :{
                            string addr1= cmd.getAddress1();
                            string addr2=cmd.getAddress2();
                       
                            std::size_t foundAddr1 = addr1.find_first_of("$.");
                            std::size_t foundAddr2 = addr2.find_first_of("$.");
                             if(foundAddr1!=std::string::npos && addr1.size()>1){
                                cout << "Bad address 1 :" << addr1 << endl;
                               
                                    cmd.setStatus(false);
                                    cmd.setStatusMsg("Bad address 1 :"+addr1);
                                 
                                break;
                             }
                             if(foundAddr2!=std::string::npos && addr2.size()>1){
                                cout << "Bad address 2 :" << addr2 << endl;
                                
                                    cmd.setStatus(false);
                                    cmd.setStatusMsg("Bad address 2 :"+addr2);
                                 
                                break;
                             }
                             string numberic{"0123456789.$-"}; //Checking for non-numeric character
                             std::size_t foundNonNumInAddr1 = addr1.find_first_not_of(numberic);
                             std::size_t foundNonNumInAddr2 = addr2.find_first_not_of(numberic);
                             if(foundNonNumInAddr1!=std::string::npos){
                                cout << "Bad Address 1: " << addr1 << endl;
                                
                                    cmd.setStatus(false);
                                    cmd.setStatusMsg("Bad address 1 :"+addr1);
                                 
                             }
                             else if (foundNonNumInAddr2!=std::string::npos){
                                cout << "Bad Address 2: " << addr2 << endl;
                                
                                    cmd.setStatus(false);
                                    cmd.setStatusMsg("Bad address 2 :"+addr2);
                                  
                             }
                             else{
                                validateLineAddresses(addr1,addr2);
                                //Populate the clipBoard
                                std::list<string>::iterator range_begin = buffer.begin();
                                std::list<string>::iterator range_end = buffer.begin();
                                std::advance(range_begin, (stoi(addr1) -1));
                                std::advance(range_end,stoi(addr2));
                          
                                std::list<string>::iterator range_ClipBoard = range_begin;
                               for(;range_ClipBoard!=range_end && range_ClipBoard!=buffer.end() ;++range_ClipBoard){
                                     
                                        clipBoard.push_back(*range_ClipBoard);
                                }

                                //delete the element from buffer.
                                int addr1_index =std::distance(buffer.begin(),range_begin);
                                int addr2_index=std::distance(buffer.begin(),range_end)-1;
                               // cout << "addr1_index : " << addr1_index<< endl;
                                //cout << "addr2_index : " << addr2_index<< endl;
                                if(addr2_index !=buffer.size()-1){                                   
                                     buffer.erase (range_begin,range_end);                                   
                                     currentLine=(std::distance(buffer.begin(),range_end))+1;                                 

                                }else if (addr1_index != 0 ){                         
                                
                                    buffer.erase (range_begin,range_end);                                
                                    currentLine=addr1_index;
                                  

                                }else{
                                    buffer.erase (range_begin,range_end);
                                    buffer.clear();
                                    currentLine=0;
                                }
                                fileStatus="updated"; // user made edit in this session                    


                             }

                      }
                      break;

            case 'J' :{
                        //Validation checks on addr1 and addr2
                        string addr1= cmd.getAddress1();
                        string addr2=cmd.getAddress2();
                     
                      
                       
                        std::size_t foundAddr1 = addr1.find_first_of("$.");
                        std::size_t foundAddr2 = addr2.find_first_of("$.");
                        if(foundAddr1!=std::string::npos && addr1.size()>1){
                              cout << "Bad address 1 :" << addr1 << endl;
                              
                                    cmd.setStatus(false);
                                    cmd.setStatusMsg("Bad address 1 :"+addr1);
                                    
                                break;
                        }
                        if(foundAddr2!=std::string::npos && addr2.size()>1){
                                cout << "Bad address 2 :" << addr2 << endl;
                                
                                    cmd.setStatus(false);
                                    cmd.setStatusMsg("Bad address 2 :"+addr2);
                                   
                                break;
                        }
                        string numberic{"0123456789.$-"}; //Checking for non-numeric character
                        std::size_t foundNonNumInAddr1 = addr1.find_first_not_of(numberic);
                        std::size_t foundNonNumInAddr2 = addr2.find_first_not_of(numberic);
                        if(foundNonNumInAddr1!=std::string::npos){
                            cout << "Bad Address 1: " << addr1 << endl;
                            
                                    cmd.setStatus(false);
                                    cmd.setStatusMsg("Bad address 1 :"+addr1);
                                   
                        }
                        else if (foundNonNumInAddr2!=std::string::npos){
                                cout << "Bad Address 2: " << addr2 << endl;
                                 
                                    cmd.setStatus(false);
                                    cmd.setStatusMsg("Bad address 2 :"+addr2);
                                    
                        }else{
                             validateLineAddresses(addr1,addr2);
                             std::list<string>::iterator range_begin = buffer.begin();
                             std::list<string>::iterator range_end = buffer.begin();
                             std::advance(range_begin, (stoi(addr1) -1));
                             std::advance(range_end,stoi(addr2)); // not making -1 to make range_end inclusive                       
                         
                         
                             std::list<string>::iterator join_itr=range_begin;
                             string joinPlaceHolder;
                             for(;join_itr!=range_end;++join_itr){
                                    joinPlaceHolder+=*join_itr;
                             }
                           
                             //replace
                             *range_begin=joinPlaceHolder;
                             currentLine=std::distance(buffer.begin(),range_begin)+1;
                           
                          
                             ++range_begin;
                            int addr1_index =std::distance(buffer.begin(),range_begin);
                            int addr2_index=std::distance(buffer.begin(),range_end)-1;                 
                    
                            buffer.erase (range_begin,range_end);
                            fileStatus="updated";
                        }

                      }
                      break;

            case 'C' : {
                         //Validation checks on addr1 and addr2
                         string addr1= cmd.getAddress1();
                         string addr2=cmd.getAddress2();            
                        
                         std::size_t foundAddr1 = addr1.find_first_of("$.");
                         std::size_t foundAddr2 = addr2.find_first_of("$.");
                         if(foundAddr1!=std::string::npos && addr1.size()>1){
                                cout << "Bad address 1 :" << addr1 << endl;
                                
                                    cmd.setStatus(false);
                                    cmd.setStatusMsg("Bad address 1 :"+addr1);
                                  
                                break;
                          }
                         if(foundAddr2!=std::string::npos && addr2.size()>1){
                                cout << "Bad address 2 :" << addr2 << endl;
                               
                                    cmd.setStatus(false);
                                    cmd.setStatusMsg("Bad address 2 :"+addr2);
                                   
                                break;
                         }
                         string numberic{"0123456789.$-"}; //Checking for non-numeric character
                         std::size_t foundNonNumInAddr1 = addr1.find_first_not_of(numberic);
                         std::size_t foundNonNumInAddr2 = addr2.find_first_not_of(numberic);
                         if(foundNonNumInAddr1!=std::string::npos){
                                cout << "Bad Address 1: " << addr1 << endl;
                                 
                                    cmd.setStatus(false);
                                    cmd.setStatusMsg("Bad address 1 :"+addr1);
                                   
                         }
                          else if (foundNonNumInAddr2!=std::string::npos){
                                cout << "Bad Address 2: " << addr2 << endl;
                                
                                    cmd.setStatus(false);
                                    cmd.setStatusMsg("Bad address 2 :"+addr2);
                                    
                          }else {
                             validateLineAddresses(addr1,addr2);
                             cout << "change ? ";
                             string oldText;
                             //cin>>skipws;
                             getline(cin,oldText);
                             
                             cout << "to ? ";
                             string updatedText;
                             //cin>>skipws;
                             getline(cin,updatedText);
                             
                             std::list<string>::iterator range_begin = buffer.begin();
                             std::list<string>::iterator range_end = buffer.begin();
                             std::advance(range_begin, (stoi(addr1) -1));
                             std::advance(range_end,stoi(addr2)); // not making -1 to make range_end inclusive in erase
                           
                          
                             for(;range_begin!=range_end;++range_begin){
                                string strToUpdate= *range_begin;                     
                              
                                std::size_t found = strToUpdate.find(oldText);
                                if(found!=std::string::npos){//Atleast one change is made.
                                    currentLine=std::distance(buffer.begin(),range_begin)+1;
                                }
                                while(found!=std::string::npos){
                                 
                                    strToUpdate.replace(found,oldText.size(),updatedText);
                                    if(found+1>buffer.size()) break;
                                    found=strToUpdate.find(oldText,found+oldText.size());
                                }
                             
                                *range_begin=strToUpdate;
                             }
                           


                             fileStatus="updated"; // user made edit in this session
                         

                          }


                       }
                       break;

            case 'V' :{
                          string addr1= cmd.getAddress1();
                          string addr2= cmd.getAddress2();						  
                          bool addr2Usable=true; // to make ("v100,1") to work!
                          std::size_t foundAddr1 = addr1.find_first_of("$.");
                          std::size_t foundAddr2 = addr2.find_first_of("$.");
                           if(foundAddr1!=std::string::npos && addr1.size()>1){
                                    cout << "Bad address 1 :" << addr1 << endl;
                                    
                                    cmd.setStatus(false);
                                    cmd.setStatusMsg("Bad address 1 :"+addr1);
                                   
                                    break;
                           }
                           if(foundAddr2!=std::string::npos && addr2.size()>1){                                
                                addr2Usable=false;                               
                             }

                             string numberic{"0123456789.$-"}; //Checking for non-numeric character
                             std::size_t foundNonNumInAddr1 = addr1.find_first_not_of(numberic);
                             std::size_t foundNonNumInAddr2 = addr2.find_first_not_of(numberic);
                             if (foundNonNumInAddr2!=std::string::npos){                             
                                 addr2Usable=false;
                              }
                               if(foundNonNumInAddr1!=std::string::npos){
                                    cout << "Bad Address 1: " << addr1 << endl;
                                  
                                    cmd.setStatus(false);
                                    cmd.setStatusMsg("Bad address 1 :"+addr1);
                                   
                            }else {
                                    validateLineAddress(addr1);
                                    if(addr2Usable){
                                        validateLineAddresses(addr1,addr2);
                                    }         
                                 

                                    std::list<string>::iterator range_begin = buffer.begin();
									if (stoi(addr1) == 0) {
										std::advance(range_begin, stoi(addr1));
									}
									else {
										std::advance(range_begin, (stoi(addr1) - 1));
									}                                    
                                    if(clipBoard.size()!=0){
                                        std::vector<string>::iterator vectItr=clipBoard.begin();
                                        for(;vectItr!=clipBoard.end();++vectItr){
                                            buffer.insert(range_begin,*vectItr);
                                           
                                        }
                                        currentLine=std::distance(buffer.begin(),range_begin);//not doing +1
                                        //cout << "Current Line after :" << currentLine << endl;
                                        fileStatus="updated";
                                        clipBoard.clear(); // empty the clipBoard
                                    }else{
                                        cout <<"ClipBoard empty , no paste" << endl;
                                    }
                            }
                      }
                      break;

            case 'U' :{
                            if(currentLine-1 == 0){
                                currentLine=1;
                                cout<<"BOF reached"<<endl;
                            }
                            else{
                                --currentLine;
                                int elementNum=1;
                            list<string>::iterator bufferItr=buffer.begin();
                            for(;bufferItr!=buffer.end();bufferItr++){
                                if(elementNum==currentLine){
                                       cout << currentLine << ">" << *bufferItr<< endl;
                                }
                                    elementNum++;
                                }//End of for loop!
                          }

                      }
                       break;
            case 'N' :{
                        if(currentLine == buffer.size()){
                            currentLine=buffer.size();
                            cout<<"EOF reached"<<endl;
                        }else{
                            ++currentLine;
                            int elementNum=1;
                            list<string>::iterator bufferItr=buffer.begin();
                            for(;bufferItr!=buffer.end();bufferItr++){
                              if(elementNum==currentLine){
                                cout << currentLine << ">" << *bufferItr<< endl;
                            }
                             elementNum++;
                            }//End of for loop!
                        }
                      }
                      break;
            default:
                        cout << "Bad Command :" << cmd.getSymbol() << endl;

            } // end of switch

     }else {
            cout << cmd.getStatusMsg() << endl;
    } // endl of else



}
