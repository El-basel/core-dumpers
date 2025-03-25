#include "SortedLinkedList.h"
#include <iostream>

using namespace std;

int main() {
    SortedLinkedList L;

    cout << "Test 1\n";
    L.insert(5);
    L.insert(8);
    L.insert(7);
    L.insert(6);
    L.insert(6);
    cout << L;
    // Expected Output: 5 6 6 7 8

    cout << "Test 2\n";
    cout << L[2] << '\n';
    // Expected Output: 6

    cout << "Test 3\n";
    L.remove(0);
    cout << L;
    // Expected Output: 6 6 7 8
    L.remove(100);
    cout << L;
    // Expected Output: 6 6 7 8 (no change)
    L.remove(2);
    cout << L;
    // Expected Output: 6 6 8
    L.remove(2);
    cout << L;
    // Expected Output: 6 6

    cout << "Test 4\n";
    SortedLinkedList list1;
    list1.remove(0);
    list1.remove(100);
    cout << list1;
    // Expected Output: (empty line)

    cout << "Test 5\n";
    SortedLinkedList list2;
    list2.insert(42);
    list2.remove(0);
    cout << list2;
    // Expected Output: (empty line)

    cout << "Test 6\n";
    SortedLinkedList list3;
    list3.insert(5);
    list3.insert(4);
    list3.insert(3);
    list3.insert(2);
    list3.insert(1);
    cout << list3;
    // Expected Output: 1 2 3 4 5

    cout << "Test 7\n";
    SortedLinkedList list4;
    list4.insert(10);
    list4.insert(20);
    list4.insert(30);
    list4.insert(40);
    list4.insert(50);
    list4.remove(0);
    list4.remove(3);
    cout << list4;
    // Expected Output: 20 30 40

    cout << "Test 8\n";
    SortedLinkedList list5;
    list5.insert(1);
    list5.insert(2);
    list5.insert(3);
    list5.remove(100);
    cout << list5;
    // Expected Output: 1 2 3 (no change)

    cout << "Test 9\n";
    SortedLinkedList list6;
    for (int i = 100000; i >= 1; i--) {
        list6.insert(i);
    }
    cout << list6[0] << " " << list6[99999] << endl;
    // Expected Output: 1 100000

    cout << "Test 10\n";
    SortedLinkedList list7;
    for (int i = 1; i <= 10; i++) {
        list7.insert(i);
    }
    for (int i = 0; i < 10; i++) {
        list7.remove(0);
    }
    cout << list7;
    // Expected Output: (empty line)

    cout << "Test 11\n";
    SortedLinkedList list8;
    list8.insert(10);
    list8.insert(20);
    list8.insert(30);
    try {
        cout << list8[100] << endl;
        // No output expected, should throw exception
    } catch (std::out_of_range &e) {
        cout << "Exception caught: " << e.what() << endl;
        // Expected Output: Exception caught: index out of bounds
    }

    cout << "Test 12\n";
    SortedLinkedList list9;
    list9.insert(1);
    list9.insert(2);
    list9.insert(3);
    list9.insert(4);
    list9.insert(5);
    for (int i = 4; i >= 0; i--) {
        list9.remove(i);
    }
    cout << list9;
    // Expected Output: (empty line)

    cout << "Test 13\n";
    SortedLinkedList list10;
    list10.insert(5);
    list10.insert(5);
    list10.insert(5);
    list10.insert(5);
    list10.insert(5);
    list10.remove(2);
    cout << list10;
    // Expected Output: 5 5 5 5
    return 0;
}
