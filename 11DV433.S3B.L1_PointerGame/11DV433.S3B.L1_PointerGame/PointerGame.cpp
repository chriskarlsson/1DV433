//-----------------------------------------------------------------------
// File:    PointerGame.cpp
// Summary: Prints parts of char array to show how pointers function
// Version: 1.0
// Owner:   Christoffer Karlsson
//-----------------------------------------------------------------------
// Log:   2017-11-29 File modified by Christoffer
//-----------------------------------------------------------------------

// pointerGame.cpp
#include <iostream>
#include <cstring>
using namespace std;

int  main()
{
    const int  ARRSIZE = 27;
    char alpha[ARRSIZE] = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
    char *ptr = alpha;
    // Print the array
    cout << "alpha is now: " << alpha << endl;

    // Print the array using the pointer and then the value of the element ('A')
    cout << ptr << " (=ptr) is not the same as " << *ptr << " (=*ptr)" << endl;
    // Print the value of the using two diffenrent syntaxes
    cout << "but " << *ptr << " (=*ptr) is the same as " << ptr[0] << " (=ptr[0]) " << endl;
    // Print the 25th element using two different syntaxes
    cout << ptr[25] << " (=ptr[25]) is the same as " << *(ptr + 25) << " [=*(ptr+25)]" << endl;
    // Move the pointer to the third element
    ptr++;
    ptr++;
    ptr++;
    // Print the length difference between the arrays (3)
    cout << "\n\"ptr\" is now " << ptr - alpha << " bytes from the beginning. \n\n";
    // Print that alpha is 27 bytes and ptr is 24 bytes
    cout << "Now the string " << alpha << " is " << strlen(alpha) << " bytes long!\n" << "and the string " << ptr << " is " << strlen(ptr) << " bytes long!\n";
    strcpy(ptr, "defghijklmnopqrstuvwxyz");
    // Show that the operation above also changed alpha by printing the string and the value of the last element
    cout << alpha << " has now a happy end: " << alpha[strlen(alpha) - 1] << "\a\a\a" << endl << endl;

    // Print Goodbye using ptr
    ptr -= 3;
    cout << (char)(ptr[6] - 32) << ptr[14] << ptr[14] << ptr[3] << (char)(ptr[1] + 32) << ptr[24] << ptr[4] << endl;
}