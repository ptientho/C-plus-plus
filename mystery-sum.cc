#include <iostream>
#include <cmath>
#include <iomanip>
using namespace std;

/*
1. Prompt a user to type in a positive integer from the keyboard.
   (Examples: 1, 2, 5, 10, 15)

2. Compute sum1 = 1/12 + 1/22 + 1/32 + ... + 1/n2.  
   Use float to compute your answer.  
   Note that this will result in a maximum accuracy of 7 digits.

3. Instead of printing this sum (approximately 1.64) compute the following expression:
       result1 = sqrt(6 * sum1)
   In order to use the sqrt function you will have to #include <cmath>

4. Output result1.
   You may recognize the number you get from this. But it will not be very accurate.

5. Compute a new result (result2) the same way using a very large value for n.
   Compute a new result (result3) backwards using the same very large value for n.
       sum3 =  1/n2 + ... + 1/32 + 1/22 + 1/12. 

6. Output result2 and result3.

This is all you have to submit, but you should try to figure out which of these two 
numbers is more accurate. It should be fairly obvious which answer is better as n 
increases. Figure out how many iterations you will need before the contribution of 
1/n2 is too small and no longer matters. We will discuss in class.

Example outputs
 result1 = X.XXXXXX

   result2 = X.XXXXXX

   result3 = X.XXXXXX
*/

int main(){

    uint64_t in1;
    cout << "Enter a positive integer: ";
    cin >> in1;
    cout << "The number is(input 1): " << in1 << '\n';
 
    double sum1 = 0;
    cout << setprecision(15);
    for(uint64_t i = 1; i <= in1; i++){
        sum1 += 1.0/(i*i);
        //cout << sum1 << ' ';
    }
   
    double result1 = sqrt(6 * sum1);
      
    uint64_t in2;
    cout << "Enter a positive integer(should be very large): ";
    cin >> in2;
    cout << "The number is(input 2): " << in2 << '\n';
    
    double sum2 = 0;
    cout << setprecision(15);
    for(uint64_t i = 1; i <= in2; i++){
        sum2 += 1.0/(i*i);
        //cout << sum2 << ' ';
    }

    double result2 = sqrt(6 * sum2);
    
    uint64_t in3;
    cout << "Enter a positive integer(should be very large): ";
    cin >> in3;
    cout << "The number is(input 3): " << in3 << '\n';
    
    double sum3 = 0;
    cout << setprecision(15);
    for(uint64_t i = in3; i >= 1; i--){
        sum3 += 1.0/(i*i);
        //cout << sum3 << ' ';
    }
    
    double result3= sqrt(6 * sum3);
    
    cout << "RESULT1= " << result1 << '\n';
    cout << "RESULT2= " << result2 << '\n';
    cout << "RESULT3= " << result3 << '\n';

}




