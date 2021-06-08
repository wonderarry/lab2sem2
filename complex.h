#include <cmath>
#include <iostream>
using std::cout;

class complex {
private:
    double re;
    double im;
    static int rootSign(double value){
        if (value > 1) {return 1;}
        if (value < 0) {return -1;}
        return 0;
    }
public:
    complex(double x1 = double(), double x2 = double()): re(x1), im(x2){}

    double real(){return this->re;}
    double imag(){return this->im;}
    complex operator+(double value)  {return complex(this->re + value, this->im);}
    complex operator+(complex value)  {return complex(this->re + value.real(), this->im + value.imag());}

    complex operator-(double value)  {return complex(this->re - value, this->im);}
    complex operator-(complex value)  {return complex(this->re - value.real(), this->im - value.imag());}

    complex operator*(double value)  {return complex(this->re * value, this->im * value);}
    complex operator*(complex value)  {return complex(this->re * value.real() - this->im * value.imag(), this->re * value.imag() + this->im * value.real());}

    complex operator-() {return complex(this->re * -1, this->im * -1);}

    bool operator==(complex value)  {return (this->re == value.real() && this->im == value.imag());}
    bool operator!=(complex value)  {return (this->re != value.real() || this->im != value.imag());}

    complex squareRoot() {
        double re = this->re;
        double im = this->im;
        re = ::sqrt((::sqrt(re*re+im*im)+re)/2);
        im = float(complex::rootSign(im))*(::sqrt((::sqrt(re*re+im*im)-re)/2));
        return complex(re, im);
    }

    void print() {
        cout << real() << " + i * " << imag() << '\n';
    }

};
