#ifndef POLYNOMIAL_H
#define POLYNOMIAL_H
#include <iostream>
using namespace std;

class Polynomial {
private:
    long long order;
    long long* coefficients;
    long long rhs;
public:
    Polynomial(long long order);
    ~Polynomial();

    void input();
    void print();
    Polynomial add(Polynomial& secondAddend);
    Polynomial subtract(Polynomial& minuend);
    char sign(long long number);
    long long absolute(long long number);
};



#endif