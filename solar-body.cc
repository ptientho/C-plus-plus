#include <iostream>
#include <string>

using namespace std;
class Body {

/*
1. Complete hwBody, creating body objects that will later be used for the 
solar system simulator.
   https://github.com/StevensDeptECE/CPE553-CPP/blob/master/session03/hwBody.cc
Links to an external site.

2. Do not edit the main() function in any way.

3. Create a Body class in the same .cc file as main() that allows the program to 
   compile and function properly. Pay special attention to the included comments in 
   main() that explain how to implement the Complex class.

4. << friend
*/
private:
	string obj_name;
	double mass;
	double x, y, z;
	double r;

public:
	Body(string obj_name , double mass, double x, double y, double z, double r) : 
		obj_name(obj_name), mass(mass), x(x), y(y), z(z), r(r) {}

	friend ostream& operator <<(ostream& os, Body b) {
		return os << b.obj_name << '\t' << b.mass << '\t' << b.x << '\t' << b.y << '\t' << b.z <<'\t' << b.r <<'\n';
	}
};

int main() {
	//         name      mass(kg) x y z  radius (m)
	Body earth("earth", 5.972e24, 0,0,0, 6.371e6);
	Body moon("moon",   7.34767309e22, 384.400e6,0,0,  1.737e6);
	cout << earth << '\n';
	cout << moon << '\n';
}
	
