/*
Assignment #2
Write a C++ program for  Addition and  Multiplication of two Complex Numbers 
by overloading + and * operators. 
You have to use >>  operator to input a Complex Number and << operator to 
display a Complex Number. Overload the input and output operators. Input operator
should be able to take input in the following format: 3+4i. Output operator should
display complex number in the following format: 3+4i.
*/

#include <iostream>
#include <limits>
using namespace std;

class Complex {
    int real, imag;

public:
    Complex(int r = 0, int i = 0) {
        real = r;
        imag = i;
    }

    Complex operator+(const Complex &c) const {
        return Complex(real + c.real, imag + c.imag);
    }

    Complex operator*(const Complex &c) const {
        return Complex(real * c.real - imag * c.imag, real * c.imag + imag * c.real);
    }

    friend istream &operator>>(istream &input, Complex &c) {
        char ch;
        input >> c.real >> ch >> c.imag;
        return input;
    }

    friend ostream &operator<<(ostream &output, const Complex &c) {
        output << c.real;
        if (c.imag >= 0) {
            output << "+" << c.imag << "i";
        } else {
            output << c.imag << "i";
        }
        return output;
    }
};

int main() {
    Complex c1, c2, c3, c4;
    cout << "Enter the first complex number: ";
    cin >> c1;

    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    cout << "Enter the second complex number: ";
    cin >> c2;

    c3 = c1 + c2;
    c4 = c1 * c2;
    cout << "The sum of the two complex numbers is: " << c3 << endl;
    cout << "The product of the two complex numbers is: " << c4 << endl;

    return 0;
}
