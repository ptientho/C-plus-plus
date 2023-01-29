#include <iostream>
#include <fstream>
#include <vector>
#include <cmath>
using namespace std;

/*
	suggestion:
for this assignment:
*/
// what makes an abstract class???
class Shape {
private:
    double x,y;

public:
    static int numShapes;
    Shape(double x, double y) : x(x), y(y) {numShapes++;}
    virtual void draw(ostream& s)  = 0;
    virtual ~Shape(){}
    double getX() const{return x;}
    double getY() const{return y;}
};
int Shape::numShapes = 0;

class FilledCircle : public Shape {
private:
    double radius;
public:
    FilledCircle(double x, double y, double r) : Shape(x,y) , radius(r){}
    void draw(ostream &s) override{
        s << getX() << " " << getY() << " " << radius << " " << "0 360 arc fill" << '\n';
    }
    ~FilledCircle()override{}
};

class Circle : public Shape {
private:
    double radius;
public:
    Circle(double x, double y, double r) : Shape(x,y), radius(r){}
    void draw(ostream& s)override{
        s << getX() << " " << getY() << " " << radius << " " << "0 360 arc stroke" << '\n';
        s << '\n';
    }
    ~Circle()override{}
};


class FilledRect : public Shape {
private:
    double width, height;
public:
    FilledRect(double x, double y, double w, double h) : Shape(x,y), width(w), height(h){}
    void draw(ostream &s)override{
        double x1 = getX() + width; double y1 = getY();
        double x2 = x1; double y2 = y1 - height;
        double x3 = x2 - width; double y3 = y2;

        s << getX() <<" "<< getY() <<" "<< "moveto" << '\n';
        s << x1 <<" "<< y1 <<" "<< "lineto" << '\n';
        s << x2 <<" "<< y2 <<" "<< "lineto" << '\n';
        s << x3 <<" "<< y3 <<" "<< "lineto" << '\n';
        s << "closepath fill" << '\n';
        s << '\n';
    }
    ~FilledRect()override{}
};

class Rect : public Shape {
private:
    double width, height;
public:
    Rect(double x, double y, double w, double h) : Shape(x,y), width(w), height(h){}
    void draw(ostream &s)override{
        double x1 = getX() + width; double y1 = getY();
        double x2 = x1; double y2 = y1 - height;
        double x3 = x2 - width; double y3 = y2;

        s << getX() <<" "<< getY() <<" "<< "moveto" << '\n';
        s << x1 <<" "<< y1 <<" "<< "lineto" << '\n';
        s << x2 <<" "<< y2 <<" "<< "lineto" << '\n';
        s << x3 <<" "<< y3 <<" "<< "lineto" << '\n';
        s << "closepath stroke" << '\n';
        s << '\n';
    }
    ~Rect()override{}
};

class Line : public Shape {
private:
    double x2, y2;
public:
    Line(double x1, double y1, double x2, double y2) : Shape(x1,y1), x2(x2), y2(y2){}
    void draw(ostream &s)override{
        s << getX() << " " << getY() << " " << "moveto" << " " << x2 << " " << y2 << " " << "lineto stroke" << '\n';
        s << '\n';
    }
    ~Line()override{}
};

class Polygon : public Shape {
private:
    double radius, rxi, ryi;
    int n;
public:
    Polygon(double x, double y, double r, int n) : Shape(x,y), radius(r), n(n){}
    void draw(ostream& s) {
        double d_degree = 360.0 / n;
        s << getX() + radius <<" "<< getY() <<" "<< "moveto" << '\n';
        for(int i = 1; i <= n; i++){
            rxi = radius - radius*cos((d_degree*M_PI) / 180);
            ryi = radius*sin((d_degree*M_PI) / 180);

            s << rxi <<" "<< ryi <<" "<< "rlineto" <<" "<< d_degree <<" "<< "rotate" << '\n';
        }
        s << "stroke" << '\n';
        s << '\n';
    }
};

class RGB : public Shape{
private:
    double red, green, blue;
public:
    RGB(double x, double y, double r, double g, double b) : Shape(x,y), red(r), green(g), blue(b){}
    void draw(ostream &s)override{
        s << red << " " << green << " " << blue << " " << "setrgbcolor" << '\n';
    }
    ~RGB()override{}
};

class Drawing {
private:
	ofstream f;
	vector<Shape*>  shapes;
public:
	explicit Drawing(const string& filename) : f(filename.c_str()), shapes() {
	    setCanvas(f);
	}
	~Drawing() { // write destructor
    //delete each individual pointer in the shapes list!
        for(int i =0; i < Shape::numShapes; i++){
            cout << "Shape " << i << " is deleted." << '\n';
            delete shapes[i];
        }
	}
	void add( Shape* s ) {
    shapes.push_back(s);
	}

	void draw() {
		for (int i = 0; i < Shape::numShapes ; i++)
			shapes[i]->draw(f);
	}

	void setrgb(double r, double g, double b) {
        add(new RGB(0,0,r,g,b));
    }

    void setCanvas(ostream& s) {
        s << "<< /PageSize [1000 1000] >> setpagedevice" << endl;
        s << "<< /BeginPage {250 250 translate } >> setpagedevice" << endl;
    }
};

void printIt(Drawing& d) {
    d.draw();
}

int main() {
	Drawing d("test4.ps");
	d.setrgb(1,0,0); // set drawing color to be bright red:  1 0 0 setrgbcolor
	//d.setrgb should be equivalent to d.add(new RGB(...)) You have to make another object
	d.add(new FilledRect(100.0, 150.0, 200.0, 50)); // x y moveto x y lineto ... fill
	d.add(new Rect(100.0, 150.0, 200.0, 50));       // x y moveto x y lineto ... stroke
	for (int x = 0; x < 600; x += 100)
		d.add(new FilledCircle(x,200,50.0)); // x y r 0 360 arc fill
	d.setrgb(0,1,0); // the rest are green

	d.add(new Circle(0,0, 100)); // 0 0 100 0 360 stroke
	d.add(new Line(400,500, 600,550));
	//OPTIONAL+40%
	d.add(new Polygon(200,200, 50, 6));
  printIt(d);
}
