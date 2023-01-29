#include <iostream> 
using namespace std;

/*
1. Utilizing a loop, sum the numbers using the float data type:
   sum1F = 1/1 + 1/2 + 1/3 ... + 1/98 + 1/99 + 1/100 
   sum2F = 1/100 + 1/99 + 1/98 + ... + 1/3 + 1/2 + 1/1
   The result should be approximately 5.18.

2. Utilizing a loop, sum the numbers using the double data type:
   sum1D = 1/1 + 1/2 + 1/3 ... + 1/98 + 1/99 + 1/100 
   sum2D = 1/100 + 1/99 + 1/98 + ... + 1/3 + 1/2 + 1/1

3. Print out sum1F, sum2F, sum1D, sum2D.
   Print out sum1F - sum2F.
   Print out sum1D - sum2D.

Demonstrate ALL results using at least 3 decimal precision.

Example outputs

sum1F = X.XXX, sum2F = X.XXX
    sum1D = X.XXX, sum2D = X.XXX
    sum1F - sum2F = X.XXX
    sum1D - sum2D = X.XXX

    *(Where X.XXX is the numerical result)*
*/
int main()
{
    float sum1F = 0;
    float sum2F = 0;
    double sum1D = 0;
    double sum2D = 0;
    //cout << sum1F << "\n";
    for(float i = 1; i <= 100; i++){
        //cout << i << "\n";
        sum1F += 1/i;
    }
    //cout << sum1F << "\n";
    
    for(float i = 100; i >= 1; i--){
        //cout << i << "\n";
        sum2F += 1/i;
    }
    //cout << sum2F << "\n";
    
    for(double i = 1; i <= 100; i++){
        //cout << i << "\n";
        sum1D += 1/i;
    }
    //cout << sum1D << "\n";
    
    for(double i = 100; i >= 1; i--){
        //cout << i << "\n";
        sum2D += 1/i;
    }
    cout << "sum1F = " << sum1F << ", sum2F = " << sum2F << "\n";
    cout << "sum1D = " << sum1D << ", sum2D = " << sum2D << "\n";
    //cout << sum2D << "\n";
    cout << "sum1F - sum2F = " << sum1F - sum2F << "\n";
    cout << "sum1D - sum2D = " << sum1D - sum2D << "\n";

}