// A simple employee database program.

/*Tasks

11. Instead of having an array for the name, one for the phone number, one for the hours and one for the salary,
it is better to create a structure for this information and make an array of structures.
(This is covered in the study questions for step 3)

a) Create a structure template named Employee with the same field names as the four arrays
b) Create a personnel directory as an array of Employee with the size REG_SIZE.
c) The original arrays should thereafter be deleted
d) Adjust the rest of the code so that it will have a good function with the new setup
e) Create columns in the output using setw() so that printing looks good. Use existing constants for the names and
phone numbers in setw(). 
NOTE 1! Strings are usually printed left aligned in the column and numeric values are right-aligned. Use the
manipulators 'left' and 'right' to control the adjustment. NOTE! Manipulators for printing - except setw() - remains
in effect until they are changed and need not be repeated.
NOTE 2! When printing floating points, you should put the decimal places and formats before printing so that
the result is as desired. cout << fixed << setprecision(2) << showpoint; is suitable here.

Also add a headline to the table. Eg like this:

Name                          Phonenumber      Pay for the week
------------------------------------------------------------------
Von Duck                      0703-233 333                 1000.32
Af Gyllenskalp                0480-322 233                  750.00
*/

#include <iostream>
#include <iomanip>
using namespace std;

const int REG_SIZE = 2;
const int NAME_SIZE = 30;
const int PHONE_SIZE = 30;

struct Employee {
    char name[NAME_SIZE];    // this array holds employee names
    char phone[PHONE_SIZE];  // their phone numbers
    float hours;             // hours worked per week
    float wage;               // wage
};

Employee personnelDirectory[REG_SIZE];

int menu();
void enter(), report();
void userInput(char *message, char *target, int targetLength);
void userInput(char *message, float *value);
void userInput(char *message, int *value);

int main()
{
    int choice;

    do 
    {
        choice = menu(); // Get selection

        switch(choice) 
        {
        case 0: 
            break;
        case 1: enter();
            break;
        case 2: report();
            break;
        default: cout << "Not a valid menu option. Please try again.\n";
        }
    } while(choice != 0);

    return 0;
}

// Returns a user's selection.
int menu()
{
    int value;

    userInput("0. Quit\n"
        "1. Enter information\n"
        "2. Report information\n"
        "\nChoose one: ",
        &value);

    return value;
}

// Enter information.
void enter()
{
    for(int i = 0; i < REG_SIZE; i++)
    {
        userInput("Enter last name: ", personnelDirectory[i].name, NAME_SIZE);   // NAME_SIZE is a dimensioned length of name
        userInput("Enter phone number: ", personnelDirectory[i].phone, PHONE_SIZE);
        userInput("Enter number of hours worked: ", &personnelDirectory[i].hours);
        userInput("Enter wage: ", &personnelDirectory[i].wage);
    }

    cout << '\n';
}

// Read user input as string
void userInput(char *message, char *target, int targetLength)
{
    cout << message;
    cin.getline(target, targetLength);   // NAME_SIZE is a dimensioned length of name
    if (cin.fail())    // If we read too many characters, the error flag is set, which blocks entry
    {
        cin.clear();            // Reset stream status
        cin.ignore(80, '\n');    // Clear up to 80 trailing characters from input buffer, 
                                 // or until the newline character ('\n') is found
    }
}

// Read user input as float
void userInput(char *message, float *value)
{
    const int FLOATLENGTH = 21;
    char str[FLOATLENGTH] = "";
    char *endptr;

    while (true)
    {
        userInput(message, str, sizeof(str) / sizeof(char));
        *value = strtof(str, &endptr);

        if (*endptr == '\0')
        {
            return;
        }

        cout << "Not a valid number. Please try again.\n";
    }
}

// Read user input as int
void userInput(char *message, int *value)
{
    const int INTLENGTH = 21;
    char str[INTLENGTH] = "";
    char *endptr;

    while (true)
    {
        userInput(message, str, sizeof(str) / sizeof(char));
        *value = strtol(str, &endptr, 0);

        if (*endptr == '\0')
        {
            return;
        }

        cout << "Not a valid number. Please try again.\n";
    }
}

// Display report.
void report()
{
    // Print headers
    cout << setw(30) << left << "Name"
        << setw(25) << left << "Phonenumber"
        << setw(25) << right << "Pay for the week" << endl;
    cout << setfill('-') << setw(80) << "" << endl;

    // Print values
    for(int i = 0; i < REG_SIZE; i++)
    {
        cout << setfill(' ') << setw(30) << left << personnelDirectory[i].name
            << setw(25) << left << personnelDirectory[i].phone
            << setw(25) << right << fixed << setprecision(2) << showpoint << personnelDirectory[i].wage * personnelDirectory[i].hours
            << endl;
    }

    cout << endl;
}

//the result is as desired.cout << fixed << setprecision(2) << showpoint; is suitable here.
//
//Also add a headline to the table.Eg like this:
//
//Name                          Phonenumber      Pay for the week     
//------------------------------------------------------------------
//Von Duck                      0703 - 233 333                 1000.32
//Af Gyllenskalp                0480 - 322 233                  750.00