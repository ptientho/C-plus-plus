// HW5A - Shapes Postscript
// Author: Peera Tienthong & Yoohan Ko

#include <iostream>
#include <fstream>
#include <vector>
#include <cmath>
using namespace std;

/*
	suggestion:
for this assignment:
*/

class Shape {
private:
    double x0,y0;
public:
    static int numShapes;
    Shape(double x, double y) : x0(x), y0(y){
        numShapes++;
    }
    virtual void draw(ostream& s) = 0;
    double getX(){return x0;}
    double getY(){return y0;}
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

class FilledRect : public Shape {
private:
    double width,height;
public:
    FilledRect(double x, double y, double w, double h): Shape(x,y), width(w), height(h){}
    void draw(ostream& s) {
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

};

class Rect : public Shape {
private:
    double width,height;
public:
    Rect(double x, double y, double w, double h): Shape(x,y), width(w), height(h){}
    void draw(ostream& s) {
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
};

class FilledCircle : public Shape {
private:
    double radius;
public:
    FilledCircle(double x, double y, double r) : Shape(x,y), radius(r){}
    void draw(ostream& s) {
        s << getX() << " " << getY() << " " << radius << " " << "0 360 arc fill" << '\n';
    }
};

class  Circle : public Shape {
private:
    double radius;
public:
    Circle(double x, double y, double r) : Shape(x,y), radius(r){}
    void draw(ostream& s) {
        s << getX() << " " << getY() << " " << radius << " " << "0 360 arc stroke" << '\n';
        s << '\n';
    }
};

class Line : public Shape {
private:
    double x2, y2;
public:
    Line(double x1, double y1, double x2, double y2): Shape(x1,y1), x2(x2), y2(y2){}
    void draw(ostream& s) {
        s << getX() << " " << getY() << " " << "moveto" << " " << x2 << " " << y2 << " " << "lineto stroke" << '\n';
        s << '\n';
    }
};

class Drawing {
private:
	ofstream f;
	vector<Shape*> shapes;
public:
	Drawing(string filename) : f(filename.c_str()), shapes() {
        setCanvas(this->f);
	}
	void add( Shape* s ) {
    shapes.push_back(s);
	}

	void draw() {
		for (int i = 0; i < Shape::numShapes ; i++)
			shapes[i]->draw(f);
	}

	void setrgb(double r, double g, double b){
	    //ostream& s = 0;
        // when setrgb is called, print out shapes vector and clear vector
        draw(); // first call draw function to print out shapes up until now
        shapes.clear(); // clear shape vector
        Shape::numShapes = 0; // reset numShapes to 0
	    f << r << " " << g << " " << b << " " << "setrgbcolor" << '\n';
	}

    void setCanvas(ostream& s) {
        s << "<< /PageSize [1000 1000] >> setpagedevice" << endl;
        s << "<< /BeginPage {250 250 translate } >> setpagedevice" << endl;
    }
};

int Shape::numShapes = 0;
int main() {
	ofstream f(  );
	Drawing d("test2.ps");
	d.setrgb(1,0,0); // set drawing color to be bright red:  1 0 0 setrgbcolor
	d.add(new FilledRect(100.0, 150.0, 200.0, 50)); // x y moveto x y lineto ... fill   (x,y,w,h)
	d.add(new Rect(100.0, 150.0, 200.0, 50));       // x y moveto x y lineto ... stroke (x,y,w,h)
	for (int x = 0; x < 600; x += 100)
		d.add(new FilledCircle(x,200,50.0)); // x y r 0 360 arc fill    (x,y,r)
	d.setrgb(0,1,0); // the rest are green

	d.add(new Circle(0,0, 100)); // 0 0 100 0 360 stroke
    d.add(new Line(400,500, 600,550));  //  (x1,y1,x2,y2)
    d.add(new Polygon(200,200, 50, 6)); //  (x,y,r) starting ar x+r,y
	d.draw();
}
