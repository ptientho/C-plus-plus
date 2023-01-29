#include <string>
#include <sstream>
#include <fstream>
#include <iostream>
#include <cmath>
#include <random>
using namespace std;

class Vec3d {
private:
	double x,y,z;	
public:

	Vec3d(double x = 0, double y = 0,double z = 0) : x(x), y(y), z(z) {}
};

class Body {

private:
	string name;
	double mass;   // mass of the body
	double radius; // size of the body (assumes spherical)
	Vec3d pos;     // pos = (x,y,0) ignore z for now. x,y should be based on orbital radius
	Vec3d v;       // v = 0 next week we have to calculate
	Vec3d a;       // a = 0 next week we compute gravitational acceleration due to all other bodies
	double perihelion, alphelion;

public:
  	
	Body() : name(), pos(), v(), a() {}

  	
	friend ostream& operator <<(ostream& s, const Body& b) {
		return s << b.name << '\t';

	}
	

  	friend istream& operator >>(istream& s, Body&  b) {
		string line;
		string Orbits;
		getline(s, line, '\n');
		//cout << line << '\n';
		istringstream sline(line);
		
		sline >> b.name >> Orbits >> b.mass >> b.radius >> b.perihelion >> b.alphelion;
		b.radius /= 2;
		//cout << b.name << '\t' << Orbits << '\t' << b.mass <<'\t'<< b.radius <<'\t'<< b.perihelion <<'\t'<< b.alphelion << '\n';
		//b.name = Name; b.mass = stod(Mass); b.radius = stod(Diam) / 2; b.perihelion = stod(Perihelion); b.alphelion = stod(Alphelion); 
		return s;
	}

	double average_dist() const{
		return (perihelion + alphelion) / 2;
	}
	void set_pos(double& d) {
		
		const double min = 0;
		const double max = 2*M_PI;
		
		double t = min + (double)(rand()) / (double)(RAND_MAX/(max - min));
		double x = d * cos((t*M_PI)/180);
		double y = d * sin((t*M_PI)/180);

		Vec3d pos(x,y,0);
	}	
};

int main() {
	
	ifstream solarsystem("solarsystem.dat");
	char buf[1024];
	solarsystem.getline(buf, sizeof(buf)); // throw out first line

	Body sun, mercury, venus, earth, moon;

	solarsystem >> sun >> mercury >> venus >> earth; // >> mercury >> venus >> earth >> moon;


	// read in the name of each body
	// compute average distance of each body from sun (average of perihelion and aphelion)
	// pick t = a random number from 0 to 2*pi
	// calculate x,y = r cos t, r sin t
	// put into pos vector (x,y, 0)

	// next step (not necessary this week)
	// calculate V
	// pretend all orbits are circular
	// calculate the length of the circular path around the sun 2*pi * r
	// look up time it takes to orbit
	// convert to meters and seconds
	// v = distance around the sun / orbital period in seconds
	cout << sun << mercury << venus << earth;
}
