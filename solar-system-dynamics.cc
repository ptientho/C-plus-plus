#include <iostream>
#include <vector>
#include <fstream>
#include "string"
#include "sstream"
#include "cmath"

using namespace std;
const double GRAVITY = 6.667E-11;

// put your Vec3d implementation here
class Vec3d {
private:
    double x,y,z;
public:
    Vec3d(double x, double y,double z) : x(x), y(y), z(z) {}
    Vec3d() : x(0), y(0), z(0) {}
    friend Vec3d operator -(const Vec3d& left, const Vec3d& right) {
        return Vec3d(left.x - right.x, left.y - right.y, left.z - right.z);
    }
    friend Vec3d operator +(const Vec3d& left, const Vec3d& right) {
        return Vec3d(left.x + right.x, left.y + right.y, left.z + right.z);
    }
    friend Vec3d operator *(Vec3d& a, double& dt) {
        return Vec3d((a.x)*dt, (a.y)*dt, (a.z)*dt);
    }
    double magsq(){
        return pow(x,2) + pow(y,2) + pow(z,2);
    }
#if 0
    Vec3d normalize(){
        return Vec3d(x/ sqrt(this->magsq()), y/ sqrt(this->magsq()), z/ sqrt(this->magsq()));
    };
#endif
    double getX() const{
        return x;
    }
    double getY() const {
        return y;
    }
    double getZ() const {
        return z;
    }
    friend ostream & operator <<(ostream& s, Vec3d v) {
        return cout <<'('<< v.x <<' '<< v.y <<' '<< v.z << ')';
    }
};

// put your Body implementation here
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
    static int numBodies;
    Body() {numBodies++;}

    friend istream& operator >>(istream& s, Body&  b) {
        string line;
        string Orbits;
        getline(s, line, '\n');
        //cout << line << '\n';
        istringstream sline(line);

        sline >> b.name >> Orbits >> b.mass >> b.radius >> b.perihelion >> b.alphelion;
        b.radius /= 2;

        return s;
    }
    friend ostream& operator <<(ostream& s, Body* b) {
        return cout << b->name <<' '<<"pos: "<< b->pos <<' '<<"v: "<< b->v <<' '<<"a: "<< b->a;
    }

    double average_dist() { //average dist of each body to sun
        return (perihelion + alphelion) / 2;
    }

    void set_pos(double d) { //set initial position for this body

        const double min = 0;
        const double max = 2*M_PI;

        double t = min + (double)(rand()) / (double)(RAND_MAX/(max - min));
        double x = d * cos((t*M_PI)/180);
        double y = d * sin((t*M_PI)/180);
        pos = Vec3d(x,y,0);
    }

    Vec3d set_acceleration(const Body* b){ //set acceleration pull due to object b

        Vec3d dpos = (b->pos - this->pos);
        double rsq = dpos.magsq();
        double acc = (GRAVITY * b->mass) / rsq;
        //Vec3d dpos = (b->pos - this->pos).normalize();
        double r = sqrt(rsq);
        double ax = (acc * dpos.getX())/ r;
        double ay = (acc * dpos.getY())/ r;
        double az = (acc * dpos.getZ())/ r;

        return Vec3d(ax,ay,az);
        //cout << a << '\n';
    }
    Vec3d set_velo(Vec3d& acc, const Body* b){
        Vec3d dpos = (b->pos - this->pos);
        double rsq = dpos.magsq();
        double r = sqrt(rsq);
        double acc_mag = sqrt(acc.magsq());
        double vx = (sqrt(acc_mag * r) * dpos.getX() )/r;
        double vy = (sqrt(acc_mag * r) * dpos.getY() )/r;
        double vz = (sqrt(acc_mag * r) * dpos.getZ() )/r;

        return Vec3d(vx,vy,vz);
    }
/*
    void set0_a() {
        a = (0,0,0);
    }
    void set0_v() {
        v = (0,0,0);
    }
*/
    void step_v(Vec3d& velo, Vec3d& acc, double& dt) {
        a = acc;
        v = velo + a*dt;
    }
    void step_pos(Vec3d& velo, Vec3d& acc,double& dt) {
        double s = 0.5;
        Vec3d a1 = acc*dt;
        Vec3d a2 = a1*dt;
        a = a2;
        pos = pos + v*dt + a*s;
    }

};
int Body::numBodies = 0;

class SolarSystem {
private:
  vector<Body*> bodies; //list of body objects
  ifstream f;
  Vec3d* acc;
  Vec3d* velo;// sum of acceleration to each body object
public:
    SolarSystem(const string& filename) : f(filename.c_str()){
        //read in the file create Body, and add to Body using addBody
        char buf[1024];
        string line;
        f.getline(buf, sizeof(buf)); // throw out first line
        while(!f.eof()){
            Body* b = new Body();
            f >> *b;
            //cout << b << '\n';
            this->addBody(b);
        }
        //cout << Body::numBodies << '\n';
        //set initial position velocity and acceleration for each object
        for(int i =0; i < Body::numBodies; i++){
            double d = bodies[i]->average_dist();
            //cout << d << '\n';
            bodies[i]->set_pos(d);
            //bodies[i]->set0_a();
            //bodies[i]->set0_v();
            //cout << bodies[i] << '\n';
        }
        acc = new Vec3d[Body::numBodies];
        velo = new Vec3d[Body::numBodies];
        //cout << acc[2];
    }
    ~SolarSystem(){
        //delete all body objects
        for(int i =0; i < Body::numBodies; i++){
            //cout << *bodies[i] << " is deleted." << '\n';
            delete bodies[i];
        }
        delete [] acc;
        delete [] velo;
    }

    void addBody(Body* b) {
        bodies.push_back(b);
    }

    void stepForward(double& s){
        for(int i = 0; i < Body::numBodies; i++){
            for(int j = 0; j < Body::numBodies; j++){
                if(i == j) {acc[i] = acc[i] + Vec3d(); velo[i] = velo[i] + Vec3d();}
                else{
                    acc[i] = acc[i] + bodies[i]->set_acceleration(bodies[j]);
                    velo[i] = velo[i] + bodies[i]->set_velo(acc[i],bodies[j]);
                }
            }
            bodies[i]->step_v(velo[i], acc[i], s);
            bodies[i]->step_pos(velo[i], acc[i], s);
        }

    }

    friend ostream& operator <<(ostream& o, SolarSystem& s) {
            return o << s.bodies[0] <<'\n'
                    << s.bodies[1] << '\n'
                    << s.bodies[2] << '\n'
                    << s.bodies[3] << '\n'
                    << s.bodies[4] << '\n'
                    << s.bodies[5] << '\n'
                    << s.bodies[6] << '\n'
                    << s.bodies[7] << '\n'
                    << s.bodies[8] << '\n'
                    << s.bodies[9] << '\n'
                    << s.bodies[10] << '\n'
                    << s.bodies[11] << '\n'
                    << s.bodies[12] << '\n'
                    << s.bodies[13] << '\n';
        //return o << s.bodies[1];
    }

};

int main() {
	/*
	1. read in the solar system from the file
  2. Your SolarSystem class should have a list (vector) of Body objects
  3. for each row in the file, add a body. Calculate the initial position for 
     each body as last week. Note that for now we will not be giving you moons
     because they orbit not the sun but other planets. This will be added later.

  4. Each body should calculate the acceleration due to the gravitational pull
     of all the others bodies. This requires vector math, which you should write
     in Vec3d.
     For any body m, the accelation due to another body m2 is:

     a = Gm2/rsq,   rsq = (pos2 - pos).magsq()
     G = universal gravitational constant 6.667E-11

     To calculate the vector acceleration, you must break down a into components
     dpos = (pos2 - pos).normalize 
     (compute a unit vector in the direction of body2)

     ax = a * dpos.x/r, ay = a * dpos.y/r, az = a * dpos.z/r

     r = magnitude of dpos.

		 If you can do this calculation within vector, it is a generically useful
		 one but you can also just compute it in Body if you want.

		 Sum up all accelerations.

		 for each body i
       set acceleration of body i = 0
		   for each body j
         add acceleration of body j on i unless j == i
       end
     end

     when you have the acceleration of all bodies, step forward in time for a timestep dt with:

    for each body b
     b.pos = b.pos + b.v * dt + 0.5 * b.a * dt*dt
     b.v = b.v + b.a * dt;

    dt is delta time (double precision) and should not be huge. 
    Start with 1000 seconds and see what happens. If 
    one body is in a sharply changing orbit, dt may have to be reduced.
    For the above to work you will have to implement some operators in Vec3d.


    v^2/r = a
		v = sqrt(ar)
	*/
  SolarSystem s("solarsystem.dat");
	cout << s << "=========\n\n\n"; // print the solar system at load time
    double incre = 1000;
	for (int i = 0; i < 31556; i++) {
        //double incre = 1000;
	    s.stepForward(incre); // step forward in time by 1000 seconds
	}

	// the loop should step forward in time by about a year. We are simplifying
	// the orbit to a circle, so the numbers will be off a bit.
	cout << s << "=========\n\n\n"; // print the solar system after the year
}
	
