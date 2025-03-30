#include "Polynomial.h"

//=================Implementation=================\\

Polynomial::Polynomial(long long order) {
    this->order = order;
    this->coefficients = new long long [order + 1];
    this->rhs = 0;
}

Polynomial::Polynomial(ifstream &inputFile) {
    inputFile >> order;
    this->coefficients = new long long [order + 1];

    inputFile >> rhs;
    for (long long i = 0; i <= order; i++) {
        inputFile >> coefficients[i];
    }
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
        //Skip printing any coeff multiplied by 0
        if (this->coefficients[i] == 0) continue;

        //Print signs
        if (!first) cout << " " << sign(this->coefficients[i]) << " ";

        //Skip printing 1's and -1's multiplied by x (except the constant)
        if (absolute(this->coefficients[i]) != 1 || i == 0) cout << absolute(this->coefficients[i]);

        //print the x
        if (i > 1) cout << "x^" << i;
        if (i == 1) cout << "x";

        first = false;
    }
    cout << " = ";
    if (sign(this->rhs) == '-') cout << "- ";
    cout << absolute(this->rhs) << endl;
}

Polynomial Polynomial::add(Polynomial& secondAddend) {
    //Get the max order to create a polynomial with the needed size
    long long maxOrder;
    this->order >= secondAddend.order ? maxOrder = this->order : maxOrder = secondAddend.order;
    Polynomial result(maxOrder);

    //Fetch each corresponding coefficients to add them
    for (long long i = 0; i <= maxOrder; i++) {
        long long firstCoeff = (i <= this->order) ? this->coefficients[i] : 0;
        long long secondCoeff = (i <= secondAddend.order) ? secondAddend.coefficients[i] : 0;
        result.coefficients[i] = firstCoeff + secondCoeff;
    }

    //Add the RHS
    result.rhs = this->rhs + secondAddend.rhs;
    
    return result;
}

Polynomial Polynomial::subtract(Polynomial& minuend) {
    //Get the max order to create a polynomial with the needed size
    long long maxOrder;
    this->order >= minuend.order ? maxOrder = this->order : maxOrder = minuend.order;
    Polynomial result(maxOrder);

    //Fetch each corresponding coefficients to subtract them
    for (long long i = 0; i <= maxOrder; i++) {
        long long firstCoeff = (i <= this->order) ? this->coefficients[i] : 0;
        long long secondCoeff = (i <= minuend.order) ? minuend.coefficients[i] : 0;
        result.coefficients[i] = firstCoeff - secondCoeff;
    }

    //Subtract the RHS
    result.rhs = this->rhs - minuend.rhs;
    
    return result;
}

