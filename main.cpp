#include "StatisticalCalculation.h"
using namespace std;

void startTest(StatisticalCalculation<double>& test) {
    cout << "Median: " << test.findMedian() << endl;
    cout << "Minimum: " << test.findMin() << endl;
    cout << "Maximum: " << test.findMax() << endl;
    cout << "Mean: " << test.findMean() << endl;
    cout << "Summation: " << test.findSummation() << endl;
    cout << "Sorted Array: ";
    test.displayArray();
    cout << endl;
}

void runManual() {
    long long number;
    cout << "Enter the number of elements: ";
    cin >> number;
    StatisticalCalculation<double> test(number);
    test.inputData();
    test.statisticsMenu();
}

void runTest() {
    ifstream inputFile("test.txt");
    if (!inputFile) {
        cout << "Error opening file test.txt\n";
        cout << "Please make sure of the naming and directory of the file\n";
        exit(0);
    }

    while (!inputFile.eof()) {
        StatisticalCalculation<double> test(inputFile);
        startTest(test);
    }
}

int main() {
    int choice;
    cout << "Welcome to the Statistical Calculator!" << endl;
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
        default:
            cout << "Exiting..." << endl;
        return 0;
    }
}