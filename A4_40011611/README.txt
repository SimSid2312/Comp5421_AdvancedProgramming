a) Assignment Number :  4
b) Name: Simran Sidhu
   Student Id: 40011611
c) Steps to run the code on Visual Studio .
================================================
1. Download the files in a folder
2. Open Visual Studio and create an empty project
3. Rt click on HeaderFiles folder of this project and click on Add and click on existing and upload all header files (xxx.h)
AcuteTriangle.h	
Rectangle.h
Rhombus.h
RightTriangle.h
Shape.h
SlotMachine.h
Triangle.h
	
4. Rt click on SourceFile folder of this project and click on Add and click on existing and upload files all cpp files (xxx.cpp)

AcuteTriangle.cpp
Rectangle.cpp
Rhombus.cpp
RightTriangle.cpp
Shape.cpp
SlotMachine.cpp
Triangle.cpp
shape_slotmachine_driver.cpp

5. Please Note before running the code add below mentioned header file :

Add below statement in shape_slotmachine_driver.cpp
using Grid = vector<vector<char>>;

Add #include<string> headerfile in shape_slotmachine_driver.cpp, otherwise below command will produce error :
 cout << rect.toString() << endl;

(Note: However in my subsmission the file : shape_slotmachine_driver.cpp , i have added the #include<string>)
==================================================

d) Additional Features : 

-> In case when the slot machine game ends due 0 token - instead of displaying  "Be sure you cash in your remaining  0  tokens at the bar!" . I will display a message - "No slot Token remaining!"
-> Also I added a validation on userBet entered by user that will remove any leading or trailing spaces.

e) List of know bugs in program : NONE

f) Note To TA :

As per my email to you regarding the confusion and overlapping nature of if conditions of 3x bet and 2x bet.

-> My interpretation is that a win is 3 x bet if any two or three shapes are similar (based on professor email comment to me "Imagine three same shapes and of the same size." ) 
  and "any (this word is mentioned in the algorithm) 2 match up in screen area" - which i interpret as that it is not necessary for just same shape to match up in the Screen Area.

  Also he sent me another email on this subject where he provided me with answer to his comment - "Imagine three same shapes and of the same size."
  He writes "The case where we have three same shapes and of the same size satisfies the first test, 3 x bet."

-> My interpretation is that a win is 2 x bet : when the above condition is not holding true the flow will go to next if and check if all the three shape are similar and its true the user wins 2 x bet.

-> Also please see snapshot of the my source code in the folder :Output of my submission.

Please feel free to contact me in case of any concerns  at : simrantechm@gmail.com

