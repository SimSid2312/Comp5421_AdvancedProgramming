#include<array>
#include<iostream>
using std::array;
using std::ostream;
using std::istream;
/**
	Assignment 3, Quad.h
	Purpose: This is a header file for Quad ADT
	@author Simran Sidhu
*/

class Quad{
    private :
         array<long long int,4> standardZeroQuad={0,1,0,1}; // Stores the standard Zero Quad
         array<long long int,4> quads; //Stores a Quad
    public :
        //Parameterized ctor
        Quad (const long long int& =0,const long long int& =1,const long long int& =0,const long long int& =1);
        //defaulted copy ctor
        Quad(const Quad &)=default;
        //defaulted assignment operator
        Quad & operator=(const Quad &)=default;
        //defaulted virtual dtor
        virtual ~Quad()=default;

        //Setter and getter Functions
        long long int get_1() const;
        long long int get_2() const;
        long long int get_3() const;
        long long int get_4() const;
        void set_1(const long long int &);
        void set_2(const long long int &);
        void set_3(const long long int &);
        void set_4 (const long long int &);


        Quad inverse() const;//inverse of a quad x
        void normalize(); //normalize x
        void reduce();//reduces x
        void standardize();// both reduces and normalizes x
        bool isEqual(const Quad &) const;//Equal ?
        bool isSimilar(const Quad &)const;//Quad IsSimilar Quad
        bool isSimilar(const long long int &)const;//Quad isSimilar k_quad
        double norm() const; //norm of x
        double absoluteValue();//absolute of x
        Quad conjugate();// conjugate of x

        //Compound Assignment Operators - quad op quad
        Quad & operator+=(const Quad &);
        Quad & operator-=(const Quad &);
        Quad & operator*=(const Quad &);
        Quad & operator/=(const Quad &);
        //Compound Assignment Operators - quad op integer
        Quad & operator+=(const long long int &);
        Quad & operator-=(const long long int &);
        Quad & operator*=(const long long int &);
        Quad & operator/=(const long long int &);


        double operator()();//overloading of operator ()
        operator double(); // overloading of operator double

        const long long int & operator[](const int &) const; // overloading of subscript op - const version
        long long int & operator[](const int &);// overloading og subscript op - non const version


        //Unary operators : as member
        Quad & operator++();// Pre-increment
        Quad & operator--();//Pre-decrement
        Quad operator++(int);//Post-increment
        Quad operator--(int);//Post-decrement
        Quad& operator-();//Negation
        Quad& operator+();

        Quad operator^(const int &);//overloading operator ^ - XOR operator

        friend ostream& operator<<(ostream&, const Quad&);//overloads operator << as a friend
        friend istream& operator>>(istream&, Quad&);//overloads operator >> as friend
};

//Quad op Quad : Binary Arithematic Operator
Quad operator+(const Quad&, const Quad&) ;
Quad operator-(const Quad&, const Quad&) ;
Quad operator*(const Quad&, const Quad&) ;
Quad operator/(const Quad&, const Quad&) ;

//Quad op Int : Binary Arithematic Operator
Quad operator*(const Quad&, const long long int &);
Quad operator+(const Quad&, const long long int &);
Quad operator/(const Quad&, const long long int &);//defined in scalar division formula
Quad operator-(const Quad&, const long long int &);

//Int op Quad : Binary Arithematic Operator
Quad operator*(const long long int &, const Quad&);
Quad operator+(const long long int &, const Quad&);
Quad operator/(const long long int &, const Quad&);//Defined as k/x=k*x.inverse
Quad operator-(const long long int &, const Quad&);


//Quad op Quad : Relation Operator
bool operator==(const Quad &,const Quad &);
bool operator<(const Quad &,const Quad &);
bool operator<=(const Quad &,const Quad &);
bool operator>(const Quad &,const Quad &);
bool operator>=(const Quad &,const Quad &);
bool operator!=(const Quad &,const Quad &);
//Quad op Integer :Relation Operator
bool operator==(const Quad &,const long long int &);
bool operator<(const Quad &,const long long int &);
bool operator<=(const Quad &,const long long int &);
bool operator>(const Quad &,const long long int &);
bool operator>=(const Quad &,const long long int &);
bool operator!=(const Quad &,const long long int &);
//Integer op Quad : relational OPerator
bool operator==(const long long int &,const Quad &);
bool operator<(const long long int &,const Quad &);
bool operator<=(const long long int &,const Quad &);
bool operator>(const long long int &,const Quad &);
bool operator>=(const long long int &,const Quad &);
bool operator!=(const long long int &,const Quad &);

// Computes gcd of two numbers
long long int euclid_gcd(long long int,long long int);
