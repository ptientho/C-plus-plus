/*
	Make the following main work by writing a class Complex.
	In this second version you will overload operator << and use the friend syntax
	
	Replace this comment with your author information and cite as necessary.
 */
#include <iostream>
#include <string>

using namespace std;
class Complex{
private:
	double real, img;

public:
	Complex(double r, double i){ real = r; img = i;}
	Complex(double r){real = r; img = 0;}
	//Complex(double i){real = 0; img = i;}
	void print() const{
		cout << this->real << " + " << this->img << 'i' << '\n';
	}
	
	//friend Complex operator +(Complex left, Complex right);
	Complex operator +(Complex right) const{
		return Complex(real + right.real, img + right.img);
	}
	friend Complex operator -(Complex n) {
		return Complex(-1*n.real, -1*n.img);
	}
	friend Complex operator *(Complex left, Complex right) {
		return Complex((left.real * right.real) - (left.img * right.img),(left.real * right.img) + (left.img * right.real));
	}
	friend ostream& operator <<(ostream& os, Complex n){
		if(n.img < 0){
			return os << n.real << n.img << 'i';
		}else{
			return os << n.real <<"+"<< n.img << 'i';
		}
	}
};

//Complex operator -(Complex n) {
//	return Complex(-1*n.real, -1*n.img);
//}

int main() {
	const Complex a(1.0, 2.0); // create a complex number with real=1.0 imag=2.0
	const Complex b(0.5, 0.0); // real = 0.5, imag = 0.0
	const Complex c = a + b;   // overload operator + using member
	Complex d = -c; // use friend
	const Complex e = a * b;   // complex multiplication
	cout << c << '\t' << d << '\t' << e << '\n';
}
