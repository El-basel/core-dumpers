#ifndef CORE_DUMPERS_SORTED_LIST_H
#define CORE_DUMPERS_SORTED_LIST_H
#include <iostream>
using namespace std;
class node{
public:
    int data;
    node* next;
    node(int value);
};
class SortedLinkedList{
private:
    node* head;
public:
    SortedLinkedList();
    void insert(int value);
    void remove(int index);
    friend ostream& operator<<(ostream& os,const SortedLinkedList& list);
    int operator[](int index);
};

#endif //CORE_DUMPERS_SORTED_LIST_H
