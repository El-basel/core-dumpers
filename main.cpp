#include <iostream>
#include "Queue.h"
#include "DynamicArray.h"
#include <fstream>
#include <sstream>
#include <string>

using namespace std;



int minNumberOfSegmentFlips(DynamicArray<int>& arr, int k) { // Time Complexity: O(N) and Space Complexity: O(K)
    int count = 0;
    Queue<int> flips;
    for (int i = 0; i < arr.size(); i++) {
        if ((arr[i] == 0 && flips.size() % 2 == 0) || (arr[i] == 1 && flips.size() % 2 == 1)) {
            count++;
            flips.push(i + k - 1);
        }
        if (!flips.isEmpty() && flips.front() == i) flips.pop();
    }
    return flips.isEmpty() ? count : -1;
}
void readTestCasesFromFile(const string& filename) {

    ifstream file(filename);
    if (!file) {
        cout << "Error opening file: " << filename << '\n';
        return;
    }

    cout << "\n";
    string line;
    int testNum = 1;

    while (getline(file, line)) {
        stringstream header(line);
        int size, k;

        if (!(header >> size >> k) || size <= 0 || k <= 0) {
            cout << "Invalid size or k in test " << testNum << '\n';
            break;
        }

        if (!getline(file, line)) {
            cout << "Missing array for test " << testNum << '\n';
            break;
        }

        stringstream arrStream(line);
        DynamicArray<int> arr(size);
        for (int i = 0; i < size; ++i) {
            if (!(arrStream >> arr[i]) || (arr[i] != 0 && arr[i] != 1)) {
                cout << "Invalid array input in test " << testNum << '\n';
                return;
            }
        }

        cout << "Test " << testNum << ": " << minNumberOfSegmentFlips(arr, k) << '\n';
        cout << "\n" << string(90, '-') << "\n\n";
        testNum++;
    }

    file.close();
}

int main() {
    string filename;
    cout << "Enter file name without extension: ";
    cin >> filename;
    filename += ".txt";
    readTestCasesFromFile(filename);
    return 0;
}
