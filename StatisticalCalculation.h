#ifndef STATISTICALCALCULATION_H
#define STATISTICALCALCULATION_H
#include <iostream>
using namespace std;

template <typename T>
class StatisticalCalculation {
private:
    T* data;
    int size;

public:
    StatisticalCalculation(int size);
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
StatisticalCalculation<T>::StatisticalCalculation(int size) {
    this->size = size;
    data = new T[size];
}

template <typename T>
StatisticalCalculation<T>::~StatisticalCalculation() {
    delete[] data;
}

template<typename T>
void StatisticalCalculation<T>::sort() { //remove sort
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
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
    for (int i = 0; i < size; i++) {
        sum += data[i];
    }
    return sum;
}

//Utility funcitons
template<typename T>
void StatisticalCalculation<T>::displayArray() {
    for (int i = 0; i < size; i++) {
        cout << data[i] << ", ";
    }
}

template<typename T>
void StatisticalCalculation<T>::inputData() {
    cout << endl;
    for (int i = 0; i < size; i++) {
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
        std::cout << "Select a statistical calculation:" << endl;
        std::cout << "1. Find Median" << endl;
        std::cout << "2. Find Minimum" << endl;
        std::cout << "3. Find Maximum" << endl;
        std::cout << "4. Find Mean" << endl;
        std::cout << "5. Find Summation" << endl;
        std::cout << "6. Display Sorted Array" << endl;
        std::cout << "7. Exit" << endl;
        std::cout << "Enter your choice: ";

        // Input validation
        if (!(std::cin >> choice)) {  // Check if input is invalid
            std::cout << "Invalid input! Please enter a number between 1 and 7.\n";
            std::cin.clear();  // Clear the error flag
            std::cin.ignore(10000, '\n');  // Ignore invalid input
            continue;  // Restart loop
        }

        switch (choice) {
            case 1:
                std::cout << "Median: " << findMedian() << std::endl;
            break;
            case 2:
                std::cout << "Minimum: " << findMin() << std::endl;
            break;
            case 3:
                std::cout << "Maximum: " << findMax() << std::endl;
            break;
            case 4:
                std::cout << "Mean: " << findMean() << std::endl;
            break;
            case 5:
                std::cout << "Summation: " << findSummation() << std::endl;
            break;
            case 6:
                displayArray();
            break;
            case 7:
                std::cout << "Exiting menu...\n";
            break;
            default:
                std::cout << "Invalid choice! Please enter a number between 1 and 7.\n";
        }
    } while (choice != 7);
}
#endif
