Steps to run the code on Visual Studio .
-------------------------------------------------------------------
1. Open Visual Studio
2. Create a new project
	2.1 click on Visual C++
	2.2 Click on Empty Project
	2.3 Enter a Name to the Project eg. Project1
	Note- for the location - you can keep the default location and checkbox for create directory for solution as checked.

	This Step will create an empty folder structure for the project.
	
3. Add Line.cpp,LineList.cpp,LineListTestDriver.cpp to the SourceFiles.
   Add input_a.txt,input_b.txt to the Resource Files.
   Add Line.h,LineList.h to the Header Files.
(You can add these files right clicking on the above mentioned folders => add => Existing Item => Select the locations where these files are saved)

4. Important note - 
     4.1. change the file path to input_a.txt and input_b.txt inside the LineListTestDriver.cpp before 
   	running the file driver class.
     4.2 To view the terminal add a statement in LineListTestDriver.cpp
	 in main add statement , before return 0 statment.
	   system("pause");
-------------------------------------------------------------------
