#include "Polynomial.h"

//=================Implementation=================\\

Polynomial::Polynomial(long long order) {
    this->order = order;
    this->coefficients = new long long [order + 1]();
    this->rhs = 0;
}

Polynomial::~Polynomial() {
    delete[] this->coefficients;
}

void Polynomial::input() {
    cout << "Enter polynomial: ";
    cin >> this->rhs;
    for (long long i = 0; i < this->order + 1; i++) {
        cin >> this->coefficients[i];
    }
    cout << endl;
}

char Polynomial::sign(long long number) {
    return (number >= 0) ? '+' : '-';
}

long long Polynomial::absolute(long long number) {
    return (number < 0) ? -number : number;
}

void Polynomial::print() {
    bool first = true;
    for (long long i = this->order; i >= 0; i--) {
        if (this->coefficients[i] == 0) continue;
        if (!first) cout << " " << sign(this->coefficients[i]) << " ";
        cout << absolute(this->coefficients[i]);
        if (i > 1) cout << "x^" << i;
        if (i == 1) cout << "x";
        first = false;
    }
    cout << " = ";
    if (sign(this->rhs) == '-') cout << "- ";
    cout << absolute(this->rhs) << endl;
}

Polynomial Polynomial::add(Polynomial& secondAddend) {
    long long maxOrder;
    this->order >= secondAddend.order ? maxOrder = this->order : maxOrder = secondAddend.order;

    Polynomial result(maxOrder);
    for (long long i = 0; i <= maxOrder; i++) {
        long long firstCoeff = (i <= this->order) ? this->coefficients[i] : 0;
        long long secondCoeff = (i <= secondAddend.order) ? secondAddend.coefficients[i] : 0;
        result.coefficients[i] = firstCoeff + secondCoeff;
    }
    result.rhs = this->rhs + secondAddend.rhs;
    return result;
}

Polynomial Polynomial::subtract(Polynomial& minuend) {
    long long maxOrder;
    this->order >= minuend.order ? maxOrder = this->order : maxOrder = minuend.order;

    Polynomial result(maxOrder);
    for (long long i = 0; i <= maxOrder; i++) {
        long long firstCoeff = (i <= this->order) ? this->coefficients[i] : 0;
        long long secondCoeff = (i <= minuend.order) ? minuend.coefficients[i] : 0;
        result.coefficients[i] = firstCoeff - secondCoeff;
    }
    result.rhs = this->rhs - minuend.rhs;
    return result;
}