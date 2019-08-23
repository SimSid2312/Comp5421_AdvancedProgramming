Steps to run the code on Visual Studio .
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

