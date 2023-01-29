#include <iostream> 
using namespace std;

/*
1. Prompt the user to input a positive integer from the keyboard. 
   (Example: "Please enter a positive integer: ")

2. Read in the positive integer from keyboard. 
   (Example n = 5) 
   (Error handling for incorrect input types is not required)

3. If the number is odd, multiply it by 3 and add 1.
   If the number is even, divide by 2.

   Repeat these rules on each result until the number converges to 1. 

   If done properly, any positive integer will converge to 1.

4. Display ALL intermediate values with either a space, tab, or newline 
   between them, and the final result.

Example outputs
n = 5
5	16	8	4	2	1   
*/
int main()
{//prompt users to take integer
try{
int n;
cout << "Please enter a positive integer: ";
cin >> n;
if (n > 0) {
   //If the number is odd, multiply it by 3 and add 1.
   //If the number is even, divide by 2.
   cout << n << " ";
   while(n > 1){
        if(n % 2 != 0){
            n = n*3+1;
        }else{
            n/=2;
        }
        cout << n << " ";
   }
   cout << "\n"; 
} else{
    throw(n);
}
}
catch(int n){
    cout << "n is not a positive number!\n";
}

}
