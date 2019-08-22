#include<iostream>
#include <utility>
#include<vector>
#include<string>
#include<map>
#include<functional>
#include<algorithm>
#include<iterator>
#include <ctype.h>
#include<set>
using std::cout;
using std::cin;
using std::endl;
using std::pair;
using std::make_pair;
using std::vector;
using std::string;
using namespace std::placeholders;

/**
Assignment 5, A5_all.cpp
Purpose: This file has both solution to Problem1 to Problem 5 based on concepts: Container, Iterator and Algorithm
@author Simran Sidhu
*/


//-----------------------------------------------------------------------------------Problem 1 ----------------------------------------------------------------------


/*Function to check if a character is space or a punctuation
@ch (char) const reference to a char
@returns (bool) returns true if the input character is a space or a punctuation otherwise returns false
*/
bool isPunctSpace(const char & ch){
    return (isspace(ch) || ispunct(ch));
}

/*Function to check if a string is palindrome or not
@phrase (string) const reference to a string
@returns (bool) returns true if the input phrase(string) is a palindrome otherwise returns false
*/

bool is_palindrome(const std::string & phrase){
    std::string temp;
    std::string::iterator it= temp.begin();
    std::insert_iterator<std::string> insert_it (temp,it);
    std::remove_copy_if (phrase.begin(),phrase.end(),insert_it,isPunctSpace);//removed punctuation and spaces
    std::transform(temp.begin(),temp.end(),temp.begin(),[](char ch){return tolower(ch);}); //converting to all the character of phrase to lower case
    int midPoint = temp.size()/2;
    bool result = std::equal (temp.begin(),temp.begin()+midPoint,temp.rbegin());// checking if a phrase is palindrome or not.
    return result;
}

/*Tester Function for is_palindrome function
*/

void test_is_palindrome(){
    std::string str_i=std::string("Was it a car or a cat I saw?");
    std::string str_u=std::string("Was it a car or a cat U saw?");
    cout << "the phrase \""+str_i+"\" is "+ (is_palindrome(str_i)?"":"not ")+"a palindrome\n";
    cout << "the phrase \""+str_u+"\" is "+ (is_palindrome(str_u)?"":"not ")+"a palindrome\n";
}



//-----------------------------------------------------------------------------------Problem 2 ----------------------------------------------------------------------

/*Function Template second_max : finds the second largest element in a sequence of elements
@beginItr (Iterator) Iterator is the typename in the template parameter list
@endItr (Iterator) Iterator is the typename in the template parameter list
@returns (pair<Iterator,bool>) the pair's first holds the iterator pointing to the second largest element 
							   and pair's second holds a bool (true when the second largest element is found otherwise false)
*/
template<typename Iterator> //template header
pair<Iterator,bool> second_max(Iterator beginItr,Iterator endItr){ 

    int numOfElement= std::distance(beginItr,endItr);
    if(numOfElement==0){//empty R
            return std::make_pair(endItr,false);
    }
    else{
        std::set<int, std::greater<int>> tempSet(beginItr,endItr);
        if(tempSet.size()==1){
            return std::make_pair(beginItr,false);
        }
        else if (tempSet.size()>=2 ){
            std::set<int>::iterator it= tempSet.begin();
            advance(it,1);
			*beginItr = *it;
            return std::make_pair(beginItr,true);
    }

    }
}

/*Tester Function for second_max function
@vec (vector of int) sequence of element of which second largest element is to found.
*/
void test_second_max(vector<int> vec)
{
	auto retval = second_max(vec.begin(), vec.end());
	if (retval.second)
	{
		cout << "The second largest element in the vector is " << *retval.first << endl;
	}
	else
	{
		if (retval.first == vec.end())
		{
			cout << "List is empty, no elements " << endl;
		}
		else
		{
			cout << "Container elements are all equal to " << *retval.first << endl;
		}
	}
}

//-----------------------------------------------------------------------------------Problem 3----------------------------------------------------------------------


// **********version 1 : Lambda Function**********
/* Counting the number of strings in a vector with length equal to n (user inputted number) using Lambda Function
@vecstr (std::vector<std::string>) const reference to a vector of string
@n (int) length of strings to be found in the input vector of string 
@returns (int) number of strings in a vector with length equals to n (user inputted number)
*/
int testCountStringLambda(const std::vector<std::string> &vecstr,const int n)
{
    int result{ 0 };
    int sizeN{n};
    auto countStringLambda=[sizeN](std::string str) { return str.size() == sizeN;};// Creates a lambda expression named countStringLambda   
    result = count_if(vecstr.begin(),vecstr.end(),countStringLambda); //Using countStringLambda as the callable argument in the call to the count-if algorithm
   return result;

}


//*******Version 2 : Free Function *************
/*Free function
@str (std::string) const reference to a string
@(int) length of strings to be found
return (bool) true if length of string str is equal to n otherwise false
*/
bool countStringFreeFun(const std::string & str, int n){
    return (str.size() == n);
}

/* Counting the number of strings in a vector with length equal to n (user inputted number) using Free Function
@vecstr (std::vector<std::string>) const reference to a vector of string
@n (int) length of strings to be found in the input vector of string
@returns (int) number of strings in a vector with length equals to n (user inputted number)
*/
int testCountStringFreeFun(const std::vector<string> &vecstr, int n)
{
    int result{ 0 };   
    result = count_if(vecstr.begin(),vecstr.end(),std::bind(countStringFreeFun,_1,n));//Using countStringFreeFun as the callable argument in the call to the count-if algorithm
    return result;
}

//*******************version 3 : Functor***********************

/*  StringFunctor (Class) objects are used as functors in function : testCountStringFunctor
*/
class StringFunctor{
    public:
    int operator()(const std::string & str, int n){
        return (str.size() == n);
    }
};

/* Counting the number of strings in a vector with length equal to n (user inputted number) using Functors i.e function objects
@vecstr (std::vector<std::string>) const reference to a vector of string
@n (int) length of strings to be found in the input vector of string
@returns (int) number of strings in a vector with length equals to n (user inputted number)
*/
int testCountStringFunctor(const std::vector<string> &vecstr, int n)
{

	int result{ 0 };   
    StringFunctor countStringFunctor{}; //Create a functor (function object) named countStringFunctor
	result = count_if(vecstr.begin(),vecstr.end(),std::bind(countStringFunctor,_1,n));//Use countStringFunctor as the callable argument in the call to the count-if algorithm
	return result;
}

//-----------------------------------------------------------------------------------Problem 4----------------------------------------------------------------------

/* Reads a string of any number of characters from keyboard,stores it and counts the frequency of each input character (except whitespace).
*/
void charFrequency(){
    cout << "Enter one or more lines of text" << endl;
    cout << "To end input press Ctrl-Z in windows and Ctrl-D in Linux"<<endl;//Please note : upon pressing Ctrl-Z on windows press enter
    std::istream_iterator<char> itr(std::cin), eos;
    std::map<char,int> freqMap;
    for_each(itr,eos,[&freqMap](char ch){ //for_each algorithm is used to populate the character and its corresponding frequency
        if(!isspace(ch)){
            std::map<char,int>::iterator it=freqMap.find(ch);
            if(it!= freqMap.end()){
                    ++freqMap[ch];
            }
            else{
                    freqMap[ch]=1;
            }
        }
    });

	
    for (auto it = freqMap.begin(); it != freqMap.end(); ++it)//Displaying the frequency of characters
	{
		cout << it->first << " " << it->second << endl;
	}
}

//-----------------------------------------------------------------------------------Problem 5----------------------------------------------------------------------
/*
 Comparator (struct) is to define to the set how to keep the elements sorted 
 */
struct Comparator{
   bool operator() (const std::string &s1, const std::string &s2) const{
        if(s1.size()!=s2.size()){
            return (s1.size() <  s2.size());
        }
        else if(s1.size()==s2.size()){
            return (s1<s2);
        }
   }
};

/* Reads a string of any number of characters from keyboard,stores it and counts the frequency of each input character (except whitespace).
*/
void multisetUsingMyComparator(){
	std::multiset<std::string,Comparator> strSet; //an empty set which will use Comparator (struct) defined above
	std::vector<std::string> vec {"C","BB","A","CC","A","B","BB","A","D","CC","DDD","AAA"};
	std::copy(vec.begin(),vec.end(),std::inserter(strSet,strSet.begin())); //copying vector element to our set using general inserter
	std::ostream_iterator<std::string> out(cout ," "); //creating an ostream_iterator for writing to cout using a space " " as separator
	std::copy(strSet.begin(),strSet.end(),out);//output the set elements to cout separating them with a space
}


int main() {

	// problem 1:
	test_is_palindrome();
	cout << "\n";

	// problem 2:   
	std::vector<int> v1{ 1 }; // one element
	test_second_max(v1);

	std::vector<int> v2{ 1, 1 }; // all elements equal
	test_second_max(v2);

	vector<int> v3{ 1, 1, 3, 3, 7, 7 }; // at least with two distict elements
	test_second_max(v3);
	cout << "\n";

	// problem 3
	std::vector<std::string> vecstr{ "count_if","Returns","the","number","of","elements","in","the",
		"range","[first","last)","for","which","pred","is","true." };
	cout << testCountStringLambda(vecstr, 5) << endl;
	cout << testCountStringFreeFun(vecstr, 5) << endl;
	cout << testCountStringFunctor(vecstr, 5) << endl;
	cout << "\n";

	// problem 4:
	charFrequency();
	cout << "\n";

	//problem 5
	multisetUsingMyComparator();
	cout << "\n";

	system("pause");
	return 0;
}