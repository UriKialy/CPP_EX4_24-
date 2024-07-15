#include "Complex.hpp"
using namespace std;

Complex::Complex(double real, double imag) : real(real), imag(imag) {}

double Complex::get_real() const
{
    return real;
}
double Complex::get_imag() const
{
    return imag;
}
Complex Complex::operator+(const Complex &other) const
{
    return Complex(real + other.real, imag + other.imag);
}
Complex Complex::operator-(const Complex &other) const
{
    return Complex(real - other.real, imag - other.imag);
}
bool Complex::operator==(const Complex &other) const
{
    return real == other.real && imag == other.imag;
}
bool Complex::operator!=(const Complex &other) const
{
    return !(*this == other);
}
bool Complex::operator>(const Complex &other) const
{
    return (real > other.real) && (imag > other.imag);
}
bool Complex::operator<(const Complex &other) const
{
    return (!(*this > other)&& !(*this == other));
}

ostream &operator<<(ostream &out, const Complex &c)
{
    out << c.real << " + " << c.imag << "i";
    return out;
}


istream &operator>>(istream &in, Complex &c)
{
    string str;
    in >> str;
    size_t pos = str.find('+');
    string real = str.substr(0, pos);
    string imag = str.substr(pos + 1, str.size() - pos - 2);
    c.real = stod(real);
    c.imag = stod(imag);
    return in;
}
std::string Complex::to_string(Complex &c) const
{
    return (std::to_string(c.get_real()) + " + " + std::to_string(c.get_imag()) + "i");
}
