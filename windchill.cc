#include <iostream>
#include <cmath>
#include <iomanip>
using namespace std;
/*1. Using the NOAA windchill table in the provided URL, generate a duplicate table.
       https://www.weather.gov/safety/cold-wind-chill-chart (Links to an external site.)

2. There is no external input to this program.
   You will be calculating each value using the formula shown on the table.
   In the formula, T = Temperature(F), V = Wind (mph).
   Use the math function pow(x,y) to compute the power.

3. Output the duplicate table as accurately as possible to the real table:
      - Round the calculated values to the same number of digits as the real table
      - Include the left-most column of given wind speeds (mph)
      - Include the top-most row of given temperatures (F)
      - Uniformly space the table
      - It is not necesary to include the color gradient, or any text labels
      - Useful tools for formatting include: iomanip, setprecision(), setw(), and '\t'.*/
double windChill(float& v, float& t){
    cout << setprecision(2);
    return 35.74 + floor(0.6215 * t) - 35.75 * pow(v,0.16) + 0.4275 * t * pow(v,0.16);
}


int main(){
    
    float v = 5, t = 40;

    //first row is temperature column
    cout << setw(7);
    for(double k = t; k >= -45; k-=5){
        cout << k << setw(5);;
    }
    cout << '\n';
    for(int j = 0; j < 12; j++){
        if(j == 0) cout << setw(2);
        for(int i = 0; i <= 18; i++){
            
            if(i == 0) cout << v << setw(5);
            else{
                cout << ceil(windChill(v,t)) << setw(5);
                t -= 5;
                }
        
        }
        
    cout << '\n';
    t = 40;
    v += 5;
    }










}