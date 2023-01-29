#include <iostream>
#include <fstream>
#include <sstream>
//#include <string>
using namespace std;

int main() {
    ifstream f("DovKruger.calendar");
    string line,c1,c2,c3;
    while(getline(f,line)) {

        if(line.empty()) {
            break;
        }
        //check if the line start with #
        if(line[0] == '#') {
            continue;
        } else {
            istringstream s(line);
            s >> c1 >> c2 >> c3;
            cout << c1 << '\t' << c2 << '\t' << c3 <<'\n';
        }

    }

}