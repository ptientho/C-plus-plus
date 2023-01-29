#include <iostream> 
using namespace std;

/*
1. Prompt a user to type in a positive integer from the keyboard.
   (Examples: 1, 2, 5, 10, 15)

2. Your program must handle TWO types of incorrect user inputs:
   A. If the user inputs a negative integer, notify the user and 
      reprompt to enter a "positive number".
   B. If the user inputs a decimal value, notify the user and reprompt 
      to enter a "whole number".

3. Compute the factorial of the positive integer.
   Example: 5 factorial = 5! = 5 * 4 * 3 * 2 * 1 = 120

4. Print out both the user input number and the calculated result.

Example outputs

Enter a positive integer:

    *User enters in -6*

  NO! Enter a POSITIVE integer:

    *User enters in 5.5*

  NO! Enter a positive INTEGER ("whole number"):

    *User enter in 10

  10! = 3628800
*/

int main()
{
    double d;
    int i;
    int product = 1;
    //prompt
    cout << "Please enter a positive integer: ";
    cin >> d;
    cout << "User enters in " << d << "\n";
    i = d;
    //cout << "Your number is " << i << "\n";
    while (d <= 0 || d - i != 0)
    {
        if(d <=0){
            //reenter a positive number
            cout << "Not a positive number. Re-enter a number: ";
            cin >> d;
            cout << "User enters in " << d << "\n";
            i = d;
        }
        if(d - i != 0){
            //reenter a whole number
            cout << "Not a whole number. Re-enter a number: ";
            cin >> d;
            cout << "User enters in " << d << "\n";
            i = d;
        }    
    }
    for(int e = i; e >= 1; e--){
        product *= e;
    }
    cout << i << "! = " << product << "\n";

}