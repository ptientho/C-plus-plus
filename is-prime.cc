#include <iostream>
using namespace std;

bool isPrime(int in){

    if(in <= 1)
        return false;
    for(int i = 2; i < in; i++){
        if(in % i == 0)
            return false;
    }
    return true;
}

int main(){
/*
1. Prompt a user to type in a positive integer from the keyboard.

2. Write a function called isPrime that returns true if the number is prime 
   and false if it is not. 
   The isPrime function will be of bool data type.

3. Output your result to include what number was tested and the result.

Example outputs
Please enter a positive integer:

          *User enters 2753*

    The number 2753 is: PRIME

    Please enter a positive integer:

          *User enters 4000000*

    The number 4000000 is: NOT PRIME
*/
unsigned int num;
cout << "Enter a positive integer: ";
cin >> num;
if(isPrime(num))
    cout << "The number " << num << " is: PRIME"<< '\n';
else    
    cout << "The number " << num << " is: NOT PRIME"<< '\n';

}