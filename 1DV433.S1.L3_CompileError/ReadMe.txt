This program shall be compiled and linked from the command line and edited by 
Notepad or a similar text editor. (Graphical development tools should not be used,
in order to get clear about which files are created for the C++-program.)

Description is based on Microsoft Visual Studio 2008-2013
=================================================================================

Where it says "P:" you can change the device to your own disk, for instance "C:".

1. Set paths to the compiler through the Start menu, by opening:
 
All Programs 
	-> Microsoft Visual Studio 2013 
		-> Visual Studio Tools 
			-> Developer Command Prompt for VS2013
			   (or equivalent in other VS versions...) 
	

2. When the Command Prompt-window appears, type "cd .." <Enter> as many times as 
	needed to make your drive (P: or C: or ?) as current drive. 

3. Use the "cd" command (which stands for "change directory") to set the path 
	"1dv433(cpp)\step1\3_compileerror" to the current folder 
	(or other location where you saved the folder structure).

4. Compile the source file using the command "cl -c -EHsc compileerror.cpp"
	(NOTE! The commands -c and -EHsc are sensitive to upper and lower case!)

5. IF errors...

	Correct them by opening the file in notepad or your editor.
	Go back and perform point 4.

   end IF

6. Link the program with the command "link " + object filename (ie "compileerror.obj")

7. Run the program: "compileerror.exe"