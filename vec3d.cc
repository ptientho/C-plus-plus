#include <cmath>
#include <iostream>

using namespace std;
class Vec3d {
private:
	double x, y, z;
public:
   //static double dot(const Vec3d& a, const Vec3d& b);
   Vec3d(double x = 0, double y = 0, double z = 0) : x(x), y(y), z(z) {}
   
   friend Vec3d operator +(Vec3d left, Vec3d right){
	   return Vec3d(left.x + right.x, left.y + right.y, left.z + right.z);
   }
   friend Vec3d operator -(Vec3d left, Vec3d right){
	   return Vec3d(left.x - right.x, left.y - right.y, left.z - right.z);
   }
   friend Vec3d operator -(Vec3d input){
	   return Vec3d(-1*input.x, -1*input.y, -1*input.z);
   }
   
   static double dot(Vec3d a, Vec3d b) {
	   return a.x*b.x + a.y*b.y + a.z*b.z;
   }

   friend double dot(Vec3d e, Vec3d f);
   friend ostream& operator <<(ostream& s, const Vec3d& i){
	   return s << "(" << i.x << "," << i.y << "," << i.z << ")";
   }
   
   double dot(Vec3d f) const{
	   return x*f.x + y*f.y + z*f.z;
   }

   double mag() const{
	   return sqrt(pow(x,2) + pow(y,2) + pow(z,2));
   }

   double magSq() const{
	   return pow(x,2) + pow(y,2) + pow(z,2);
   }

   double dist(Vec3d f) const{
	   return sqrt(pow(x - f.x, 2) + pow(y - f.y, 2) + pow(z - f.z, 2));
   }
   
};

double dot(Vec3d e, Vec3d f){
	return e.x*f.x + e.y*f.y + e.z*f.z;
}

int main() {
	// Main() Section 1
	const Vec3d a(1.0,2.5,3.5); // double precision!
	const Vec3d b(2.0);         //(2,0,0)
	const Vec3d c(2.0,3.5);     //(2,3.5,0)
	const Vec3d d;              //(0,0,0)

	// Main() Section 2
	const Vec3d e = a + d;  // use friend
	const Vec3d f = c - b;	// use friend
	const Vec3d g = -e;     // use friend
	
	// Main() Section 3	
	double r = dot(e, f); // regular function  e.x*f.x + e.y*f.y + e.z*f.z  (friend)
	double s = e.dot(f); // method
	double t = Vec3d::dot(e,f); // static function

	// Main() Section 4	
	double x = e.mag(); // square root of sum of square
	double y = e.magSq(); // sum of square
	double z = e.dist(f); // sqrt or sum of square of diff

	// Main() Section 5	
	cout << "a: " << a << '\n';
	cout << "b: " << b << '\n';
	cout << "c: " << c << '\n';
	cout << "d: " << d << '\n';
	cout << "e: " << e << '\n';
	cout << "f: " << f << '\n';
	cout << "g: " << g << '\n';
	cout << "r: " << r << '\n';
	cout << "s: " << s << '\n';
	cout << "x: " << x << '\n';
	cout << "y: " << y << '\n';
	cout << "z: " << z << '\n';

}	






