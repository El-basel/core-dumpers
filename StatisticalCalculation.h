#ifndef STATISTICALCALCULATION_H
#define STATISTICALCALCULATION_H
#include <iostream>
#include <fstream>
using namespace std;

template <typename T>
class StatisticalCalculation {
private:
    T* data;
    long long size;

public:
    StatisticalCalculation(long long size);
    StatisticalCalculation(ifstream& inputFile);
    ~StatisticalCalculation();

    //Statistical calculations
    void sort();
    T findMedian();
    T findMin();
    T findMax();
    T findSummation();
    double findMean();

    //Utility
    void displayArray();
    void inputData();
    void statisticsMenu();
};

//=================Implementation=================\\

//Statistical calculations
template <typename T>
StatisticalCalculation<T>::StatisticalCalculation(long long size) {
    this->size = size;
    data = new T[size];
}

template <typename T>
StatisticalCalculation<T>::StatisticalCalculation(ifstream& inputFile) {
    inputFile >> size;
    data = new T[size];
    for (long long i = 0; i < size; i++) {
        inputFile >> data[i];
    }
    sort();
}

template <typename T>
StatisticalCalculation<T>::~StatisticalCalculation() {
    delete[] data;
}

template<typename T>
void StatisticalCalculation<T>::sort() {
    for (long long i = 0; i < size; i++) {
        for (long long j = 0; j < size; j++) {
            if (data[i] < data[j]) {
                T temp = data[i];
                data[i] = data[j];
                data[j] = temp;
            }
        }
    }
}

template<typename T>
T StatisticalCalculation<T>::findMedian() {
    if (size % 2 == 0) {
        return (data[(size / 2) - 1] + data[(size / 2)]) / 2;
    }
    else {
        return data[size / 2];
    }
}

template<typename T>
T StatisticalCalculation<T>::findMin() {
    return data[0];
}

template<typename T>
T StatisticalCalculation<T>::findMax() {
    return data[size - 1];
}

template<typename T>
double StatisticalCalculation<T>::findMean() {
    return static_cast<double>(findSummation()) / size;
}

template<typename T>
T StatisticalCalculation<T>::findSummation() {
    T sum = 0;
    for (long long i = 0; i < size; i++) {
        sum += data[i];
    }
    return sum;
}

//Utility funcitons
template<typename T>
void StatisticalCalculation<T>::displayArray() {
    bool first = true;
    for (long long i = 0; i < size; i++) {
        if (!first) cout << " , ";
        cout << data[i];
        first = false;
    }
}

template<typename T>
void StatisticalCalculation<T>::inputData() {
    cout << endl;
    for (long long i = 0; i < size; i++) {
        cout << "Enter element " << i + 1 << ": ";
        cin >> data[i];
    }
    cout << endl;
    sort();
}

template<typename T>
void StatisticalCalculation<T>::statisticsMenu() {
    int choice;

    do {
        cout << endl;
        cout << "Select a statistical calculation:" << endl;
        cout << "1. Find Median" << endl;
        cout << "2. Find Minimum" << endl;
        cout << "3. Find Maximum" << endl;
        cout << "4. Find Mean" << endl;
        cout << "5. Find Summation" << endl;
        cout << "6. Display Sorted Array" << endl;
        cout << "7. Exit" << endl;
        cout << "Enter your choice: ";

        if (!(cin >> choice)) {
            cout << "Invalid input! Please enter a number between 1 and 7.\n";
            cin.clear();
            cin.ignore(10000, '\n');
            continue;
        }

        switch (choice) {
            case 1:
                cout << "Median: " << findMedian() << std::endl;
                break;
            case 2:
                cout << "Minimum: " << findMin() << std::endl;
                break;
            case 3:
                cout << "Maximum: " << findMax() << std::endl;
            break;
            case 4:
                cout << "Mean: " << findMean() << std::endl;
                break;
            case 5:
                cout << "Summation: " << findSummation() << std::endl;
                break;
            case 6:
                displayArray();
                break;
            case 7:
                cout << "Exiting menu...\n";
            break;
            default:
                cout << "Invalid choice! Please enter a number between 1 and 7.\n";
        }
    } while (choice != 7);
}

#endif
