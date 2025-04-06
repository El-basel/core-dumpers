#include <iostream>
#include "Polynomial.h"
using namespace std;

void preformOperation(Polynomial& poly1, Polynomial& poly2) {
    //Display polynomials
    cout << "First polynomial: ";
    poly1.print();
    cout << "Second polynomial: ";
    poly2.print();

    //Sum of polynomials
    Polynomial sum = poly1.add(poly2);
    cout << "Sum of polynomials: ";
    sum.print();

    //Difference of polynomials
    Polynomial diff = poly2.subtract(poly1);
    cout << "Difference of polynomials: ";
    diff.print();
}

void runManual() {
    long long order1, order2;

    //Input for first polynomial
    cout << "Order of first polynomial: ";
    cin >> order1;
    Polynomial poly1(order1);
    poly1.input();

    //Input for second polynomial
    cout << "Order of second polynomial: ";
    cin >> order2;
    Polynomial poly2(order2);
    poly2.input();

    preformOperation(poly1, poly2);
}

void runTest() {
    ifstream inputFile("test.txt");
    if (!inputFile) {
        cout << "Error opening file test.txt\n";
        cout << "Please make sure of the naming and directory of the file\n";
        return;
    }

    int testCounter = 1;
    while (!inputFile.eof()) {
        cout << "Test #" << testCounter++ << ": " << endl;
        Polynomial poly1(inputFile);
        Polynomial poly2(inputFile);

        preformOperation(poly1, poly2);
        cout << endl;
    }
    inputFile.close();
}

int main() {
    int choice;
    cout << "Welcome to the Polynomial Calculator!" << endl;
    cout << "Choose an option from the following list:" << endl;
    cout << "1) Use the program manually." << endl;
    cout << "2) Use a test.txt file." << endl;
    cout << "0) Exit." << endl;
    cin >> choice;

    switch (choice) {
        case 1:
            runManual();
            break;
        case 2:
            runTest();
            break;
        case 0:
            cout << "Exiting..." << endl;
            return 0;
    }

}
