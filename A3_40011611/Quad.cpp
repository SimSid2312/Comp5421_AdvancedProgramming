#include<iostream>
#include <math.h>
//#include <algorithm>
#include "Quad.h"
using std::cout;
using std::cin;
using std::endl;

/**
	Assignment 3, Quad.h
	Purpose: This file is an implementation of the Quad ADT
	@author Simran Sidhu
*/

/*
 Computes GCD of two numbers
 @return (long long int) gcd of two number
*/
long long int euclid_gcd(long long int num1,long long int num2){ //Computes gcd of two numbers
    if (num2 == 0){
		return num1;
    }
	return euclid_gcd(num2, num1 % num2);
}


/*Getter function for x1
 @returns (long long int) x1
*/
long long int Quad::get_1() const{
    return quads[0];
}
/*Getter function for x2
 @returns (long long int) x2
*/
long long int Quad::get_2() const{
    return quads[1];
}
/*Getter function for x3
 @returns (long long int) x3
*/
long long int Quad::get_3() const{
    return quads[2];
}
/*Getter function for x4
 @returns (long long int) x4
*/
long long int Quad::get_4() const{
    return quads[3];
}
/*Setter function for x1
 @k is const reference (long long it) holding the value of x1
*/
void Quad::set_1(const long long int & k){
    this->quads[0]=k;
}
/*Setter function for x2
 @k is const reference (long long it) holding the value of x2
*/
void Quad::set_2(const long long int &k){
    this->quads[1]=k;
}
/*Setter function for x3
 @k is const reference (long long it) holding the value of x3
*/
void Quad::set_3(const long long int &k){
    this->quads[2]=k;
}
/*Setter function for x4
 @k is const reference (long long it) holding the value of x4
*/
void Quad::set_4 (const long long int &k){
    this->quads[3]=k;
}

/*Computes the inverse of Quad
@return (Quad)
*/
Quad Quad::inverse() const{
    Quad result;
    long long int alpha=this->get_1()*this->get_1()*this->get_4()*this->get_4() - 2* this->get_2()*this->get_2() *this->get_3()*this->get_3();
    long long int x1=this->get_1()*this->get_2()*this->get_4()*this->get_4();
    long long int x2=alpha;
    long long int x3=-(this->get_2()*this->get_2()*this->get_3()*this->get_4());
    long long int x4=alpha;

    result.set_1(x1);
    result.set_2(x2);
    result.set_3(x3);
    result.set_4(x4);

    result.standardize();
    return result;

}

/*  Checks if two quads are similar
    Returns(bool) true if x is similar to y; false otherwise
*/
bool Quad::isSimilar(const Quad &q) const{
    return (    (this->get_1()*q.get_2()==q.get_1()*this->get_2())
              &&(this->get_3()*q.get_4()==q.get_3()*this->get_4())
            );
}

/*
    Const Member Function ,checks if a quads are similar to an Integer
    @k (long long int)  is converted into k_quad
*/
bool Quad::isSimilar(const long long int & k)const{
    Quad k_quad(k);
    return(this->isSimilar(k_quad));
}

/*Quad op Quad - Basic arithematic operator (+)
 @lhs (Quad) const reference to a quad
 @rhs (Quad) const reference to a quad
 @returns (Quad) result of arithematic operator on the two input parameter
*/
Quad operator+(const Quad& lhs,const Quad& rhs) {
    Quad result{lhs};
    result+=rhs;
    return result;
}
/*Quad op Quad - Basic arithematic operator (-)
 @lhs (Quad) const reference to a quad
 @rhs (Quad) const reference to a quad
 @returns (Quad) result of arithematic operator on the two input parameter
*/
Quad operator-(const Quad&lhs,const Quad& rhs) {
    Quad result{lhs};
    result-=rhs;
    return result;
}
/*Quad op Quad - Basic arithematic operator (*)
 @lhs (Quad) const reference to a quad
 @rhs (Quad) const reference to a quad
 @returns (Quad) result of arithematic operator on the two input parameter
*/
Quad operator*(const Quad& lhs,const Quad& rhs){
    Quad result{lhs};
    result*=rhs;
    return result;
}
/*Quad op Quad - Basic arithematic operator (/)
 @lhs (Quad) const reference to a quad
 @rhs (Quad) const reference to a quad
 @returns (Quad) result of arithematic operator on the two input parameter
*/
Quad operator/(const Quad& lhs,const Quad& rhs){
    Quad result {lhs};
    result/=rhs;
    return result;
}
/*Quad op Integer - Basic arithematic operator (*)
 @lhs (Quad) const reference to a quad
 @rhs (Integer) const reference to a integer
 @returns (Quad) result of arithematic operator on the two input parameter
*/
Quad operator*(const Quad& lhs, const long long int & k){
     Quad result{lhs};
     result*=k;
     return result;
}
/*Quad op Integer - Basic arithematic operator (+)
 @lhs (Quad) const reference to a quad
 @rhs (Integer) const reference to a integer
 @returns (Quad) result of arithematic operator on the two input parameter
*/
Quad operator+(const Quad& lhs, const long long int & k){
    Quad result{lhs};
    result+=k;
    return result;
}
/*Quad op Integer - Basic arithematic operator (/)
 @lhs (Quad) const reference to a quad
 @rhs (Integer) const reference to a integer
 @returns (Quad) result of arithematic operator on the two input parameter
*/
Quad operator/(const Quad& lhs, const long long int & k){
    Quad result{lhs};
    result/=k;
    return result;
}
/*Quad op Integer - Basic arithematic operator (-)
 @lhs (Quad) const reference to a quad
 @rhs (Integer) const reference to a integer
 @returns (Quad) result of arithematic operator on the two input parameter
*/
Quad operator-(const Quad& lhs, const long long int & k){
    Quad result{lhs};
    result-=k;
    return result;
}

/*Integer op Quad - Basic arithematic operator (*)
 @lhs (Integer) const reference to a integer
 @rhs (Quad)  const reference to a quad
 @returns (Quad) result of arithematic operator on the two input parameter
*/
Quad operator*(const long long int &k, const Quad&rhs ){
     Quad result{rhs};
     result*=k;
     return result;
}
/*Integer op Quad - Basic arithematic operator (+)
 @lhs (Integer) const reference to a integer
 @rhs (Quad)  const reference to a quad
 @returns (Quad) result of arithematic operator on the two input parameter
*/
Quad operator+(const long long int & k, const Quad& rhs){
     Quad result{rhs};
     result+=k;
     return result;
}
/*Integer op Quad - Basic arithematic operator (/)
 @lhs (Integer) const reference to a integer
 @rhs (Quad)  const reference to a quad
 @returns (Quad) result of arithematic operator on the two input parameter
*/
Quad operator/(const long long int & k, const Quad&rhs){
     Quad result{rhs.inverse()};//k/x=k*x.inverse
     result*=k;
     return result;
}
/*Integer op Quad - Basic arithematic operator (-)
 @lhs (Integer) const reference to a integer
 @rhs (Quad)  const reference to a quad
 @returns (Quad) result of arithematic operator on the two input parameter
*/
Quad operator-(const long long int & k, const Quad& rhs){
    Quad result{rhs};
    result-=k;
    return result;
}

/*Quad op Quad - Compound Assignment Operators(+=)
 @rhs (Quad)  const reference to a quad
 @returns (Quad) result of arithematic operator on the input parameter and the calling Quad - modifying the calling Quad
*/
Quad & Quad::operator+=(const Quad &rhs){
   long long int x1=this->get_1()*rhs.get_2() + this->get_2()*rhs.get_1();
   long long int x2=this->get_2()*rhs.get_2();
   long long int x3=this->get_3()*rhs.get_4() + this->get_4()*rhs.get_3();
   long long int x4=this->get_4()*rhs.get_4();
   this->set_1(x1);
   this->set_2(x2);
   this->set_3(x3);
   this->set_4(x4);
   this->standardize();
   return *this;
}
/*Quad op Quad - Compound Assignment Operators(-=)
 @rhs (Quad)  const reference to a quad
 @returns (Quad) result of arithematic operator on the input parameter and the calling Quad - modifying the calling Quad
*/
Quad & Quad::operator-=(const Quad & rhs){
    long long int x1=this->get_1()*rhs.get_2() - this->get_2()*rhs.get_1();
    long long int x2=this->get_2()*rhs.get_2();
    long long int x3=this->get_3()*rhs.get_4() - this->get_4()*rhs.get_3();
    long long int x4=this->get_4()*rhs.get_4();
    this->set_1(x1);
    this->set_2(x2);
    this->set_3(x3);
    this->set_4(x4);
    this->standardize();
    return *this;
}
/*Quad op Quad - Compound Assignment Operators(*=)
 @rhs (Quad)  const reference to a quad
 @returns (Quad) result of arithematic operator on the input parameter and the calling Quad - modifying the calling Quad
*/
Quad & Quad::operator*=(const Quad &rhs){
    long long int x1=(this->get_1()*rhs.get_1()*this->get_4()*rhs.get_4())+ (2*this->get_3()*rhs.get_3()*this->get_2()*rhs.get_2());
    long long int x2=this->get_2()*rhs.get_2()*this->get_4()*rhs.get_4();
    long long int x3=this->get_1()*rhs.get_3()*rhs.get_2()*this->get_4() + rhs.get_1()*this->get_3()*this->get_2()*rhs.get_4();
    long long int x4 =this->get_2()*rhs.get_2()*this->get_4()*rhs.get_4();
    this->set_1(x1);
    this->set_2(x2);
    this->set_3(x3);
    this->set_4(x4);
    //cout << "Before stand: " << this->get_1() << " " << this->get_2() << " "<< this->get_3() << " " << this->get_4() << endl;
    this->standardize();
    return *this;
}
/*Quad op Quad - Compound Assignment Operators(/=)
 @rhs (Quad)  const reference to a quad
 @returns (Quad) result of arithematic operator on the input parameter and the calling Quad - modifying the calling Quad
*/
Quad & Quad::operator/=(const Quad & rhs){
    Quad rhs_inverse=rhs.inverse();
    long long int x1=(this->get_1()*rhs_inverse.get_1()*this->get_4()*rhs_inverse.get_4())+ (2*this->get_3()*rhs_inverse.get_3()*this->get_2()*rhs_inverse.get_2());
    long long int x2=this->get_2()*rhs_inverse.get_2()*this->get_4()*rhs_inverse.get_4();
    long long int x3=this->get_1()*rhs_inverse.get_3()*rhs_inverse.get_2()*this->get_4() + rhs_inverse.get_1()*this->get_3()*this->get_2()*rhs_inverse.get_4();
    long long int x4=this->get_2()*rhs_inverse.get_2()*this->get_4()*rhs_inverse.get_4();
    this->set_1(x1);
    this->set_2(x2);
    this->set_3(x3);
    this->set_4(x4);
    this->standardize();
    return *this;
}

/*Quad op Integer -  Compound Assignment Operators(*=)
 @k (long long int)  const reference to a Integer
 @returns (Quad) result of arithematic operator on the input parameter and the calling Quad - modifying the calling Quad
*/
Quad & Quad::operator*=(const long long int & k){
    long long int x1=k*this->get_1();
    long long int x3=k*this->get_3();
    this->set_1(x1);
    this->set_3(x3);
    this->standardize();
    return *this;
}
/*Quad op Integer -  Compound Assignment Operators(+=)
 @k (long long int)  const reference to a Integer
 @returns (Quad) result of arithematic operator on the input parameter and the calling Quad - modifying the calling Quad
*/
Quad & Quad::operator+=(const long long int & k){
    long long int x1=this->get_1()+k*this->get_2();
    this->set_1(x1);
    this->set_2(this->get_2());
    this->set_3(this->get_3());
    this->set_4(this->get_4());
    this->standardize();
    return *this;
}
/*Quad op Integer -  Compound Assignment Operators(/=)
 @k (long long int)  const reference to a Integer
 @returns (Quad) result of arithematic operator on the input parameter and the calling Quad - modifying the calling Quad
*/
Quad & Quad::operator/=(const long long int &k){
    long long int x2=k*this->get_2();
    long long int x4=k*this->get_4();
    this->set_1(this->get_1());
    this->set_2(x2);
    this->set_3(this->get_3());
    this->set_4(x4);
    this->standardize();
    return *this;
}
/*Quad op Integer -  Compound Assignment Operators(-=)
 @k (long long int)  const reference to a Integer
 @returns (Quad) result of arithematic operator on the input parameter and the calling Quad - modifying the calling Quad
*/
Quad & Quad::operator-=(const long long int & k){
    long long int x1=this->get_1()-k*this->get_2();
    this->set_1(x1);
    this->set_2(this->get_2());
    this->set_3(this->get_3());
    this->set_4(this->get_4());
    this->standardize();
    return *this;
}

/* Checking if two Quads are Equal
 @rhs (Quad) const reference to a Quad
 @return true if the calling quad is Equal to input Quad; false otherwise
*/
bool Quad::isEqual(const Quad & rhs) const{
    return (this->quads[0] == rhs.quads[0] &&
            this->quads[1] == rhs.quads[1] &&
            this->quads[2] == rhs.quads[2] &&
            this->quads[3] == rhs.quads[3]);
 }
/*
    Normalize a Quad
*/
void Quad::normalize(){
    if(this->get_2()==0){
        this->set_2(1);
    }

    if(this->get_4()==0){
        this->set_4(1);
    }

    if(this->get_2() < 0 && this->get_4()>0){
        this->set_1(-(this->get_1()));
        this->set_2(-(this->get_2()));
    }else if (this->get_2() > 0 && this->get_4() < 0){
        this->set_3(-(this->get_3()));
        this->set_4(-(this->get_4()));
    }else if(this->get_2() < 0 && this->get_4() < 0){
        this->set_1(-(this->get_1()));
        this->set_2(-(this->get_2()));
        this->set_3(-(this->get_3()));
        this->set_4(-(this->get_4()));
    }
    //cout << "Normalized: " << quads[0] << " " << quads[1] <<" "<< quads[2]<<" "<<quads[3] << endl;
}
/*
    Reduce a Quad
*/
void Quad::reduce(){
    auto gcd_X0X1=euclid_gcd(this->get_1(),this->get_2());
    auto gcd_X2X3=euclid_gcd(this->get_3(),this->get_4());
        //auto g1=__gcd(this->get_1(),this->get_2());
    //auto g2=__gcd(this->get_3(),this->get_4());
    //cout << "gcd_X0X1 : " << gcd_X0X1 << endl;
    //cout << "gcd_X2X3 : " << gcd_X2X3 << endl;
        //cout << "g1 : " << g1 << endl;
    //cout << "g2 : " << g2 << endl;
    this->set_1(this->get_1()/gcd_X0X1);
    this->set_2(this->get_2()/gcd_X0X1);
    this->set_3(this->get_3()/gcd_X2X3);
    this->set_4(this->get_4()/gcd_X2X3);
    normalize();
}
/*
    Standardize a Quad
*/
void Quad::standardize(){

    reduce();
    normalize();
}
/* Overloading Operator double - this member function calls the overloaded operator() to fetch the SquareRoot of norm of a Quad
 @return (double) - SquareRoot of norm of a Quad
*/
Quad::operator double(){
    double result = (*this)();
    return result;
}
/* Overloading Operator () - Computes SquareRoot of norm of a Quad
 @return (double) - SquareRoot of norm of a Quad
*/
double Quad::operator()(){
    return sqrt(this->norm());
}
/* Computes Norm of the calling Quad.
  @return (double) - norm of a Quad
*/
double Quad::norm() const{
    double result;
    result=((double)this->get_1()/(double)this->get_2()*(double)this->get_1()/(double)this->get_2())+
            ((double)this->get_3()/(double)this->get_4()*(double)this->get_3()/(double)this->get_4());

    return result;
}
/* Computes Conjugate of the calling Quad - modifying the calling Quad
   @return (Quad)
*/
Quad Quad::conjugate(){
    long long int x3=-(this->get_3());
    this->set_3(x3);
    this->standardize();
    return *this;
}

/*
  Parameterized Constructor of Quad - with default values of all four parameters declared in Quad.h
*/
 Quad::Quad(const long long int& k1,const long long int& k2,const long long int& k3,const long long int& k4){
     quads[0]=k1;
     quads[1]=k2;
     quads[2]=k3;
     quads[3]=k4;
     standardize();
 }
/* Operator Overloading of Subscript Operator[] - const version.
   This member function checks if the subscript is Valid; if it is return the long long int at that subscript otherwise
   throws exception invalid_argument
   @subscript (int) const reference to a subscript
   @return long long int Value at the valid subscript of Quad's container array ; otherwise throws exception
*/
const long long int & Quad::operator[](const int & subscript) const{
    //cout << "Const version called..!" << endl;
    int temp{subscript-1};
    if(temp < 0 || temp >=4){
        throw std::invalid_argument("index out of bounds");
    }
    return quads[temp];
}
/* Operator Overloading of Subscript Operator[] - non const version.
   This member function checks if the subscript is Valid; if it is return the long long int at that subscript otherwise
   throws exception invalid_argument
   @subscript (int) const reference to a subscript
   @return long long int Value at the valid subscript of Quad's container array ; otherwise throws exception
*/
long long int  & Quad::operator[](const int & subscript){
    //cout << "Non const called :" << endl;
    int temp{subscript-1};
    if(temp < 0 || temp >=4){
        throw std::invalid_argument("index out of bounds");
    }
    return quads[temp];
}
/* Computes the Unary Operator(-) i.e. Negation of a Quad - modifying it.
  @return (Quad)
*/
Quad& Quad::operator-(){//Negation
    long long int x1=-(this->get_1());
    long long int x3=-(this->get_3());
    this->set_1(x1);
    this->set_3(x3);
    this->standardize();
    return *this;
}
/* Computes the unary Operator (+) on a Quad.
  @return (Quad)
*/
Quad& Quad::operator+(){
    return *this; // Simple return statement as this operator makes no change in the Quad
}
/*Computes Pre-increment on the calling Quad - modifying the Quad.
  @ return (Quad)
*/

Quad & Quad::operator++(){
    Quad & r= *this;
    r+=1;
    return *this;
}
/*Computes Pre-decrement on the calling Quad - modifying the Quad.
  @ return (Quad)
*/
Quad & Quad::operator--(){
    Quad & r= *this;
    r-=1;
    return *this;
}
/*Computes Post-increment on the calling Quad - modifying the Quad.
  @ return (Quad)
*/
Quad Quad::operator++(int){
    Quad temp{*this}; // Copying the calling Quad - so this old value of calling Quad can be sent back to caller
    Quad & r= *this;
    r+=1; //Modifying the calling Quad
    return temp; //Return the old value of calling Quad
}
/*Computes Post-decrement on the calling Quad - modifying the Quad.
  @ return (Quad)
*/
Quad Quad::operator--(int){
    Quad temp{*this};// Copying the calling Quad - so this old value of calling Quad can be sent back to caller
    Quad & r= *this;
    r-=1;//Modifying the calling Quad
    return temp;//Return the old value of calling Quad
}
/* Overloading XOR ^ operator - to compute x ^ power - no modification made on the calling Quad
   @return (Quad) result of the raising x ^ power
*/
Quad Quad::operator^(const int &power){

    Quad result{*this};
    bool inverse=false;
    int temp_power{power};
    if(temp_power <0){ // A check if we need to inverse the result after computing x^power - in case the power < 0
        temp_power=-temp_power;
        inverse=true;
    }

    if(temp_power==0){
        Quad temp_quad;
        result=temp_quad; // in case  power =0 i.e. x ^ 0 then return - standardZeroQuad={0,1,0,1};
    }
    else if(temp_power==1){
        result=(*this); // in case power=1 i.e. x ^ 1 then return - x
    }
    else if (temp_power>1) // in case power>1 then compute the result.
    {
        int count=1;
        while(count<temp_power){

          result*=(*this);
          //cout<< "after mul: " << result.get_1() << " " << result.get_2() << " " << result.get_3() << " " << result.get_4() << endl;
          ++count;
        }
    }

    if(inverse){ // called in case the power is < 0
        result=result.inverse(); // compute the inverse of the result
    }
    result.standardize();
    return result;
}

/*Quad op Quad - Relational Operators(+=)
 @lhs (Quad) const reference to a quad
 @rhs (Quad)  const reference to a quad
 @returns (bool) true if two input parameter are Equal; false otherwise
*/
bool operator==(const Quad &lhs,const Quad & rhs){
    return(lhs.isEqual(rhs));
}
/*Quad op Quad - Relational Operators(<)
 @lhs (Quad) const reference to a quad
 @rhs (Quad)  const reference to a quad
 @returns (bool) true if norm of lhs < norm of rhs ; false otherwise
*/
bool operator<(const Quad &lhs,const Quad &rhs){
    return(lhs.norm()<rhs.norm());
}
/*Quad op Quad - Relational Operators(<=)
 @lhs (Quad) const reference to a quad
 @rhs (Quad)  const reference to a quad
 @returns (bool) true if norm of lhs <= norm of rhs ; false otherwise
*/
bool operator<=(const Quad &lhs,const Quad &rhs){
    return(lhs.norm()<=rhs.norm());
}
/*Quad op Quad - Relational Operators(>)
 @lhs (Quad) const reference to a quad
 @rhs (Quad)  const reference to a quad
 @returns (bool) true if norm of lhs > norm of rhs ; false otherwise
*/
bool operator>(const Quad &lhs,const Quad &rhs){
    return(lhs.norm()>rhs.norm());
}
/*Quad op Quad - Relational Operators(>=)
 @lhs (Quad) const reference to a quad
 @rhs (Quad)  const reference to a quad
 @returns (bool) true if norm of lhs >= norm of rhs ; false otherwise
*/
bool operator>=(const Quad &lhs,const Quad &rhs){
    return(lhs.norm()>=rhs.norm());
}
/*Quad op Quad - Relational Operators(<=)
 @lhs (Quad) const reference to a quad
 @rhs (Quad)  const reference to a quad
 @returns (bool) true if norm of lhs != norm of rhs ; false otherwise
*/
bool operator!=(const Quad &lhs,const Quad &rhs){
    return(lhs.norm()!=rhs.norm());
}

/*Quad op Integer - Relation Operators(==)
 @lhs (Quad) const reference to a quad
 @rhs (long long int)  const reference to a Integer - which is converted to Quad
 @returns (bool) true if lhs == Quad of k ; false otherwise
*/
bool operator==(const Quad &lhs,const long long int &k){
    Quad k_quad(k);
    return (lhs==k_quad);
}
/*Quad op Integer - Relation Operators(<)
 @lhs (Quad) const reference to a quad
 @rhs (long long int)  const reference to a Integer - which is converted to Quad
 @returns (bool) true if lhs < Quad of k ; false otherwise
*/
bool operator<(const Quad & lhs,const long long int &k){
    Quad k_quad(k);
    return(lhs<k_quad);
}
/*Quad op Integer - Relation Operators(<=)
 @lhs (Quad) const reference to a quad
 @rhs (long long int)  const reference to a Integer - which is converted to Quad
 @returns (bool) true if lhs <= Quad of k ; false otherwise
*/
bool operator<=(const Quad & lhs,const long long int &k){
    Quad k_quad(k);
    return(lhs<=k_quad);
}
/*Quad op Integer - Relation Operators(>)
 @lhs (Quad) const reference to a quad
 @rhs (long long int)  const reference to a Integer - which is converted to Quad
 @returns (bool) true if lhs > Quad of k ; false otherwise
*/
bool operator>(const Quad & lhs,const long long int &k){
    Quad k_quad(k);
    return(lhs>k_quad);
}
/*Quad op Integer - Relation Operators(>=)
 @lhs (Quad) const reference to a quad
 @rhs (long long int)  const reference to a Integer - which is converted to Quad
 @returns (bool) true if lhs >= Quad of k ; false otherwise
*/
bool operator>=(const Quad & lhs,const long long int &k){
    Quad k_quad(k);
    return(lhs>=k_quad);
}
/*Quad op Integer - Relation Operators(!=)
 @lhs (Quad) const reference to a quad
 @rhs (long long int)  const reference to a Integer - which is converted to Quad
 @returns (bool) true if lhs < Quad of k ; false otherwise
*/
bool operator!=(const Quad & lhs,const long long int &k){
    Quad k_quad(k);
    return(lhs!=k_quad);
}

/*Integer op Quad - Relational Operators(==)
 @lhs (long long int)  const reference to a Integer - which is converted to Quad
 @rhs (Quad) const reference to a quad
 @returns (bool) true if  Quad of k == rhs ; false otherwise
*/
bool operator==(const long long int & k ,const Quad &rhs){
    Quad k_quad(k);
    return (k_quad==rhs);
}
/*Integer op Quad - Relational Operators(<)
 @lhs (long long int)  const reference to a Integer - which is converted to Quad
 @rhs (Quad) const reference to a quad
 @returns (bool) true if  Quad of k < rhs ; false otherwise
*/
bool operator<(const long long int & k ,const Quad &rhs){
    Quad k_quad(k);
    return(k_quad<rhs);
}
/*Integer op Quad - Relational Operators(==)
 @lhs (long long int)  const reference to a Integer - which is converted to Quad
 @rhs (Quad) const reference to a quad
 @returns (bool) true if  Quad of k <= rhs ; false otherwise
*/
bool operator<=(const long long int & k,const Quad & rhs){
    Quad k_quad(k);
    return(k_quad<=rhs);
}
/*Integer op Quad - Relational Operators(>)
 @lhs (long long int)  const reference to a Integer - which is converted to Quad
 @rhs (Quad) const reference to a quad
 @returns (bool) true if  Quad of k > rhs ; false otherwise
*/
bool operator>(const long long int &k,const Quad &rhs){
    Quad k_quad(k);
    return(k_quad>rhs);
}
/*Integer op Quad - Relational Operators(>=)
 @lhs (long long int)  const reference to a Integer - which is converted to Quad
 @rhs (Quad) const reference to a quad
 @returns (bool) true if  Quad of k >= rhs ; false otherwise
*/
bool operator>=(const long long int &k,const Quad &rhs){
    Quad k_quad(k);
    return(k_quad>=rhs);
}
/*Integer op Quad - Relational Operators(!=)
 @lhs (long long int)  const reference to a Integer - which is converted to Quad
 @rhs (Quad) const reference to a quad
 @returns (bool) true if  Quad of k != rhs ; false otherwise
*/
bool operator!=(const long long int &k,const Quad &rhs){
    Quad k_quad(k);
    return(k_quad!=rhs);
}

/*Overloads operator << to output the Quad numbers
 @out (ostream)  reference of the object of ostream
 @q (Quad) const reference of the Quad object
 @returns (ostream)  reference of the object of ostream
*/
ostream& operator<<(ostream& out, const Quad& q){
     out << "[";
     for(int i=0;i<4;i++){
        if(i==3){
                out << q.quads[i] <<"]";
        }else{
                out << q.quads[i] <<", ";
        }
     }
    return out;
 }
/* Computes the absoluteValue of the calling Quad.
  @return (double) absolute value of Quad
*/
double Quad::absoluteValue(){
    double result;
    result=sqrt(this->norm());
    return result;

}

/*
Operator Overloading of operator (>>) this function takes input from the user i.e. 4 long long int and creates a Quad and returns it.
@in , reference of the object of istream
@line_obj , reference of the Quad object
@return reference of istream object
*/

istream& operator>>(istream&in , Quad& q){
    cout << "About to create the quad [a,b,c,d]" << endl;
    cout << "Enter four numbers a,b,c,d, in that order :"<< endl;
    in >> q.quads[0];
    in >> q.quads[1];
    in >> q.quads[2];
    in >> q.quads[3];
    q.standardize();
    return in;
}


