#include<iostream>
#include "LineList.h"
using std::cout;
using std::cin;
using std::endl;
/**
	Assignment 1, LineList.cpp
	Purpose: Class LineList models a linked list of text line, implementing a doubly linked list of type Node.
	Node is a class which is defined as private member(an inner class) of the LineList class.The Node object stores three values, 
	of which two point to neighboring Node objects, if any.
	@author Simran Sidhu
*/

/*
Definition of Node class which is declared as private member of class LineList
*/
class LineList::Node{
	public:
		Line data;//this node's data
		Node* prev;//pointer to the previous node
		Node* next;//pointer to the next node
		Node(const Line& ln, Node * prv, Node *nxt) {
			data = ln; 
			prev = prv;
			next = nxt;
		}
};

/*
Default constructor , initialises the two sentinal nodes - headerNode,trailerNode,head,tail and theSize datamembers of LineList
*/
LineList::LineList() {	
	std::string dummy_str="dummy";// Passing a string dummy for the line object expected by the Node's constructor for sentinal nodes/dummy nodes.
	const char * c_dummy_str = dummy_str.c_str();
	head = new Node(Line(c_dummy_str),nullptr, nullptr);//Head is made to point to a sentinal node node with prev node pointer and next node pointer pointing to nullptr
	tail = new Node(Line(c_dummy_str), nullptr, nullptr);//Tail is made to point to a sentinal node node with prev node pointer and next node pointer pointing to nullptr
	head->next = tail;//Making the head's sentinal node point to the tail node
	tail->prev = head;//Making the tail's sentinal node point to the head node
	theSize = 0; // initializing the size of the linked list
}

/*
Copy Constructor, initialises the two sentinal nodes - headerNode,trailerNode,head,tail and theSize datamembers of LineList and Populates this list with the 
datamembers of input parameter , linelist_obj if linelist_obj is not empty otherwise does nothing and simply returns
@linelist_obj a reference of the object of LineList
*/
LineList::LineList(const LineList & linelist_obj) {

	if (linelist_obj.empty()) {
		return;//input linelist is empty;
	}
	
	//initialize this list object
	std::string dummy_str = "dummy";
	const char * c_dummy_str = dummy_str.c_str();
	head = new Node(Line(c_dummy_str), nullptr, nullptr);
	tail = new Node(Line(c_dummy_str), nullptr, nullptr);
	head->next = tail;
	tail->prev = head;
	theSize = 0; // initializing the size of the linelist
	
	//Populating this list using linelist_obj
	Node * curr = linelist_obj.head->next; //curr iterates over list - linelist_obj till it reaches linelist_obj's tailernode
	while (!(curr == linelist_obj.tail)) {		
		Node * temp = tail->prev;
		tail->prev = new Node(curr->data, temp, tail);//Adding a new node to this list
		theSize++; //Increment the size (number of node) by 1
		temp->next = tail->prev;
		curr = curr->next;
	}
}


/*
Destructor of LineList Class - empty the list and deallocated the memory assigned to the head and tail node and resets the size of the list to zero
*/
LineList::~LineList() {
	
	while (!empty()) {
		pop_back();
	}
	delete head;
	delete tail;
	theSize = 0;

}

/*
Print this list 
*/
void LineList::print() const {
	Node *current = head->next;
	int counter = 0;
	while (!(current == tail)) {
		counter++;
		cout << "(" << counter << ") " << current->data.cstr() << endl;
		current = current->next;		
	}
}
/*
Checking if the list is empty
@ return true(1) if it is empty otherwise returns false(0)
*/
bool LineList::empty() const {
	//A List is empty if header and trailer nodes point to each other
	if (head->next == tail && tail->prev == head) { 
		return true;
	}
	return false;
}
/*
Returns the size of this list
@ return the size(number) of the nodes in the list - excluding the header and trailer nodes(dummy/sentinal nodes)
*/
int LineList::size() const {
	return theSize;
}
/*
Removes node at position pos in this list - if the pos values is in the range of 1 to theSize(number of nodes in the list)
 @ pos The position of the node to be removed from the list
*/
void LineList::remove(int pos) {
	/*The linked list is empty or a bad position argument (pos is greater than theSize of linkedList) or trailerNode which
		is at pos= theSize+1 or pos is trying to remove headerNode which is at pos = 0 then do nothing and return*/
	if (empty() || pos > theSize || pos==0) {		
		return;
	}
	int count = 1;
	Node *temp = head->next;	
	while (true) {
		if (count == pos) {
			temp->prev->next = temp->next; // temp is the node that is at position pos and being removed from the list
			temp->next->prev = temp->prev;
			temp->next = nullptr;//setting the next pointer of the temp node to nullPtr
			temp->prev = nullptr;//setting the tail pointer of the temp node to nullPtr
			delete temp; //de-allocate the space allocated 
			theSize--;//decrementing the size of the list by 1
			return;
		}
		else {
			temp = temp->next;//Move to the next node
			count++;//Increment the counter by 1
		}
	}
}

/*
Returns the line at position k in this list
@ pos The position of the line to be returned from this list
@return Line Object
*/
Line LineList::get(int pos) const {
	if (empty() || pos > theSize || pos <= 0) {
		//The linked list is empty or a bad position argument (pos is greatear than theSize of linkedList) or trailerNode
		// or pos is trying to remove headerNode.
		return Line("");//Returning an empty string as the line object
	}
	int count = 1;
	Node * temp = head->next;
	while (!(temp == tail)) {		
		if (count == pos) {		
			//return temp->data; // Returning the Line Object from the Node
			break;
		}
		else {
			temp = temp->next;
			count++; //Increment the counter by 1
		}

	}
	return temp->data;
}

/*
Inserts the line at the end of this list as a datamember of the node object
@ line The Line object to load inside the node object - to push to the list
*/
void LineList::push_back(const Line& line) {	
	Node * temp = tail->prev;//Take the back up of the tail's previous	
	tail->prev = new Node(line, temp, tail);//make the tail point to the new node using prev	
	temp->next = tail->prev;//make the tail's old prev's next point to the new node
	theSize++;	//Increment the size of the list by 1.
}
/*
Removes the last node in this list
*/
void LineList::pop_back() {
	Node *temp = tail->prev;
	tail->prev->prev->next = tail;
	tail->prev = tail->prev->prev;
	temp->prev = nullptr;//setting the next pointer of the temp node to nullPtr
	temp->next = nullptr;//setting the tail pointer of the temp node to nullPtr
	delete temp;//de-allocate the space allocated 
	theSize--;//decrementing the size of the list by 1
}
/*
Removes the first node in this list
*/
void LineList::pop_front() {
	Node *temp = head->next;	
	head->next->next->prev = head;
	head->next = head->next->next;
	temp->prev = nullptr;//setting the next pointer of the temp node to nullPtr
	temp->next = nullptr;//setting the tail pointer of the temp node to nullPtr
	delete temp;//de-allocate the space allocated 
	theSize--;//decrementing the size of the list by 1
}

/*
Inserts the line at the front of this list
@ line_obj A reference of the line object
*/
void LineList::push_front(const Line& line_obj) {
	Node * temp = head->next; 	//Take the back up of the head's next
	head->next = new Node(line_obj, head, temp);//make the head's next point to the new node 
	temp->prev = head->next; //make the old head's next node's previous  point to the new nodei.e current head's next 
	theSize++;//Increment the number of nodes in the list
}

/*
Inserts a new line at position k in this list
@line_obj , A reference to the line obj that needs to loaded in a node object which is to be inserted to the list at position pos
@ pos , Position where the node is to be inserted in this list
*/
void LineList::insert(const Line & line_obj, int pos) {

	int count = 1;//Keep track of the current node's position in the list
	Node *temp = head->next; //temp iterates over the list

	while (count<=theSize+1)	{ //theSize+1 -here +1 is used to make the insertion between lastnode and trailernode
		if (count == pos) {			
			Node * prevPtr = temp->prev;//take the back up of the node pointed by temp's prev pointer
			temp->prev = new Node(line_obj,prevPtr,temp); // Making an new node and add it to the list i.e current node's prev will point to this new node
			prevPtr->next = temp->prev;//Make the backup node (pointed by pointer prevPtr) next point to this new node 
			theSize++;//Increment the size of the list by 1
			return;
		}
		else
		{
			temp = temp->next; //Move to the next node
			count++;//Increment the counter by 1
		}
	}
	
}

/*
Operator Overload of operator(=) i.e copy assignment
@line_obj , A reference to the linelist object 
@return reference of the const LineList object 
*/
const LineList & LineList::operator=(const LineList& linelist_obj) {

	if (this == &linelist_obj) { //checks LHS!=RHS to proceed ahead
		return *this; 
	}

	//de-allocate the space used by this lineList object 
	while (!(this->empty())) {
		pop_back();
	}
	delete head;
	delete tail;
	theSize = 0;

	//initialize this object  once again
	std::string dummy_str = "dummy";
	const char * c_dummy_str = dummy_str.c_str();
	head = new Node(Line(c_dummy_str), nullptr, nullptr);
	tail = new Node(Line(c_dummy_str), nullptr, nullptr);
	head->next = tail;
	tail->prev = head;
	theSize = 0; // initializing the size of the linked list

	//Populate this linelist object using the linelist_obj
	Node * curr = linelist_obj.head->next;
	while (!(curr == linelist_obj.tail)) {
		Node * temp = tail->prev;
		tail->prev = new Node(curr->data, temp, tail);
		theSize++; //Increment this lineList size by 1 
		temp->next = tail->prev;
		curr = curr->next;
	}

	return *this; //returns this lineList object
}