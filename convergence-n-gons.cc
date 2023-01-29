#include <iostream>
#include <cmath>
#include <iomanip>
using namespace std;

/*
1. Start with a circle of radius = 1.
    2. Circumscribe an equilateral triangle, (n = 3) around the circle
    3. Circumscribe a circle around the triangle.
    4. Circumscribe a square (n = 4) around the circle
   5. Circumscribe a circle around the square. 
   6. Circumscribe a pentagon (n = 5) around the circle. 
   7. Keep going until n = 1,000,000 (106)
   8. Print out the circle radii for n = 10, 100, 1000, 10000, 100000, 106.

   Example outputs
    n = 10       Radius = XX.XXXXX 
    n = 100      Radius = XX.XXXXX
    n = 1000     Radius = XX.XXXXX
    n = 10000    Radius = XX.XXXXX
    n = 100000   Radius = XX.XXXXX
    n = 106        Radius = XX.XXXXX
    (Where XX.XXXXX is the value)
*/
int main(){
    double r = 1;
    uint64_t n = 3;
    double theta = 360;
    for(uint64_t i = n; i <= 1000000; i++){
        r = r / cos((theta / (i * 2)) * (3.14159265 / 180));
        if(i == 10 || i == 100 || i == 1000 || i == 10000 || i == 100000 || i == 1000000){
            cout << "n = " << i << setw(15) << "Radius = " << r << '\n';
        }
         
    } 

}