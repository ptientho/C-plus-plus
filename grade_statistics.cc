#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <cmath>
using namespace std;

/*
N
grade0 grade1 ... gradeN
*/

double stdev(double& avg, int& space, string& numset){
    double sum = 0;
    double num;
    istringstream numS(numset);
    for(int i = 1; i <= space; i++){
        numS >> num;
        sum += (num - avg)*(num - avg);
    }
    return sqrt(sum/space);
}

int main() {
    ifstream f("grades2.txt");
    string sLine, Line;
    int space = 0;
    double min,max,x;
    double sum = 0.0;
    ostringstream strNums;
    string numSet;
    while(getline(f,sLine)){
        //cout << sLine << " ";
        istringstream s(sLine);
        //x = stod(sLine);
    
        while(s >> x){
        cout << x << " ";
        if(space == 0){min = x; max = x;}
        if(x < min){min = x;}
        if(x > max){max = x;}
        sum += x;
        space += 1;
        strNums << x << " ";
        numSet = strNums.str();
        //cout << "sum: " << sum << '\n';
        }
    }
    double avg = sum/space;
    cout << '\n';
    cout << "number of space-delimited: "<< space - 1 << '\n';
    cout << "min value: " << min << '\n';
    cout << "max value: " << max << '\n';
    cout << "average: " << avg << '\n';
    cout << "standard dev: " << stdev(avg, space, numSet) << '\n';
    f.close();
}
