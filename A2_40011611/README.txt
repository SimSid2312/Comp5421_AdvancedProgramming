Steps to run the code on Visual Studio .

Important note: 
To run the editor in continuous session - 
		please comment below command in the driver class  : 
			//testLineEd(filename); // normally we'd comment out this line
		Uncomment :
			LineEd ed(filename); // create a LineED object
			ed.run();   
However if you want to run the testLineEd method in driver 
		please comment the lines in the driver class :
			LineEd ed(filename); // create a LineED object
			ed.run();             // run the line editor
		and uncomment :
			//testLineEd(filename); // normally we'd comment out this line
======================================================================================
1. Download the files in a folder
2. Open Visual Studio and create an empty project
3. Rt click on HeaderFiles folder of this project and click on Add and click on existing and upload files - 
	Command.h
	LineEd.h
4. Rt click on SourceFile folder of this project and click on Add and click on existing and upload files -
	Command.cpp
	LineEd.cpp
	LineEdDriver.cpp

5. To run the code without any filename in command line argument - simply run the driver class
	However if you want to run the editor on with a filename as argument , follow below steps to add a command line argument.
	
	(Note : In the driver class the method  testLineEd(filename); // normally we'd comment out this line
	is expecting a filename of a file that exist , hence i am  putting a file - abc.txt in the submission folder 
	for you to test this method and you can add this file in the project directory folder.
	Also please take a note of "Important note A" mentioned at the top of README )
	
	Steps to add Command Line Arguments :
	1. Add the file (eg abc.txt) to the project on visual studio :
		1.1 Right click on sourceFiles folder of the project and then click add and then click existing 
			and finally go to the directory where the file is present and upload it.(optional)
    2.  In case you want to run  method :  testLineEd(filename) please uncomment in the driver class and comment 
		lines - LineEd ed(filename);  and ed.run();  in the driver class.Otherwise skip this step.
		
	3. Rt click on the project in Visual Studio and then go to properties and then go to Configuration Property and then go to Debugging
	   Here on the right side you will see : a feild to add command argument , here please type  the filename 
	   (eg. abc.txt) and click on ok and run the code.
	   
	 
======================================================================================
	
		
	
