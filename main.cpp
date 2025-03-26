#include <iostream>
#include "StatisticalCalculation.h"
#include "Polynomial.h"
using namespace std;

int main() {
    long long order1, order2;

    // Input for first polynomial
    cout << "Order of first polynomial: ";
    cin >> order1;
    Polynomial poly1(order1);
    poly1.input();

    // Input for second polynomial
    cout << "Order of second polynomial: ";
    cin >> order2;
    Polynomial poly2(order2);
    poly2.input();

    // Display polynomials
    cout << "First polynomial: ";
    poly1.print();
    cout << "Second polynomial: ";
    poly2.print();

    // Sum of polynomials
    Polynomial sum = poly1.add(poly2);
    cout << "Sum of polynomials: ";
    sum.print();

    // Difference of polynomials (poly2 - poly1)
    Polynomial diff = poly2.subtract(poly1);
    cout << "Difference of polynomials (second - first): ";
    diff.print();

    return 0;
}