#include "SortedLinkedList.h"
#include <iostream>

using namespace std;
int main(){
    SortedLinkedList L;

    //test 1
    L.insert(5); // L = [5]
    L.insert(8); // L = [5, 8]
    L.insert(7); // L = [5, 7, 8]
    L.insert(6); // L = [5, 6, 7, 8]
    L.insert(6); // L = [5, 6, 6, 7, 8]
    cout << L; // Output: [5, 6, 6, 7, 8]


    //test 2
    cout << L[2] << '\n'; // Output: 6
    cout << L[10]; // Throws out_of_range exception


    //test 3
    L.remove(0); // L = [6, 6, 7, 8]
    cout << L; // Output: [6, 6, 7, 8]
    L.remove(100); // No change (out of bounds)
    cout << L; // Output: [6, 6, 7, 8]
    L.remove(2); // L = [6, 6, 8]
    cout << L; // Output: [6, 6, 8]
    L.remove(2); // L = [6, 6]
    cout << L; // Output: [6, 6]

    return 0;
}