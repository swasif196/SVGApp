Sohaib Wasif
0874921
CIS*2750
A3
****************************************************
To Create the shared library:

make <- compiles and creates the .so file in the SVGApp folder.
****************************************************
To delete the .so from the SVGApp folder and clear the .o files use the make command below.

make clean <- rm SVGApp/*.so, *.o
****************************************************
Header Files (*.h):

SVGParser.h <- Is essential for creating the .so shared library and is submitted in the include folder

LinkedListAPI.h <- Is essential for creating the .so shared library and is submitted in the include folder

helper.h <- Is essential for creating the .so shared library and is submitted in the include folder
****************************************************
Source Code (*.c):

SVGParser.c <- Is essential for creating the .so shared library and is submitted in the src folder

LinkedListAPI.c <- Is essential for creating the .so shared library and is submitted in the src folder

helper.c <- Is essential for creating the .so shared library and is submitted in the src folder. It mainly contain functions that communicate with Javascript.