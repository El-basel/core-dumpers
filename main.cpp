#include "SortedLinkedList.h"
#include <iostream>

using namespace std;
int main(){
    SortedLinkedList list;

    // Test Case 1: Insert elements into the sorted linked list
    list.insert(5);
    list.insert(1);
    list.insert(10);
    list.insert(3);
    list.insert(7);

    cout << "List after insertions: " << list << endl;  // Expected: 1 -> 3 -> 5 -> 7 -> 10 -> NULL

    // Test Case 2: Access elements using []
    cout << "Element at index 0: " << list[0] << endl;  // Expected: 1
    cout << "Element at index 2: " << list[2] << endl;  // Expected: 5
    cout << "Element at index 4: " << list[4] << endl;  // Expected: 10
    cout << "Element at index 5: " << list[5] << endl;  // Expected: "Index out of bounds" and -1

    // Test Case 3: Remove elements
    list.remove(2);  // Remove element at index 2 (Expected: 5)
    cout << "List after removing index 2: " << list << endl;  // Expected: 1 -> 3 -> 7 -> 10 -> NULL

    list.remove(0);  // Remove head (Expected: 1)
    cout << "List after removing head: " << list << endl;  // Expected: 3 -> 7 -> 10 -> NULL

    list.remove(10);  // Try to remove out-of-bounds index
    cout << "List after attempting to remove out-of-bounds: " << list << endl;  // Expected: No change

    // Test Case 4: Remove all elements
    list.remove(0);
    list.remove(0);
    list.remove(0);
    cout << "List after removing all elements: " << list << endl;  // Expected: NULL

    return 0;
}