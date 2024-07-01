#include <iostream>
#include <vector>
#include <string>

class Complex
{
private:
    double real;
    double imag;

public:
    Complex(double real, double imag);
    double get_real() const;
    double get_imag() const;
    Complex operator+(const Complex &other) const;
    Complex operator-(const Complex &other) const;
    Complex operator*(const Complex &other) const;
    Complex operator/(const Complex &other) const;
    bool operator==(const Complex &other) const;
    bool operator >(const Complex &other) const;
    bool operator!=(const Complex &other) const;
    std::string to_string(Complex &c) const;
    friend std::ostream &operator<<(std::ostream &out, const Complex &c);
    friend std::istream &operator>>(std::istream &in, Complex &c);
};