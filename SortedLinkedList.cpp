#include "SortedLinkedList.h"
#include <iostream>


#include "SortedLinkedList.h"

node::node(int value) {
    this->data = value;
    this->next = nullptr;
}

SortedLinkedList::SortedLinkedList() {
    this->head = nullptr;

}

void SortedLinkedList::insert(int value) {
    if (this->head == nullptr) {
        node* new_node = new node(value);
        this->head = new_node;
    }
    else {
        node* cur = this->head;
        node* prev = nullptr;
        node* new_node = new node(value);
        while (cur != nullptr) {
            if (new_node->data < cur->data) {
                if (prev == nullptr) {
                    new_node->next = cur;
                    this->head = new_node;
                }
                else {
                    prev->next = new_node;
                    new_node->next = cur;
                }
                return;
            }
            prev = cur;
            cur = cur->next;
        }
        prev->next = new_node;
    }
}

void SortedLinkedList::remove(int index) {
    if (this->head == nullptr) {
        cout << "The list is empty";
        return;
    }
    node *cur = this->head;
    node *prev = nullptr;
    if (index == 0) {
        this->head = cur->next;
        free(cur);
        return;
    }
    int i = 0;
    while (cur != nullptr && i < index) {
        prev = cur;
        cur = cur->next;
        i++;
    }
    if (cur == nullptr) {
        cout << "Out of bounds";
        return;
    }
    prev->next = cur->next;
    delete cur;
}

ostream &operator<<(ostream &os, const SortedLinkedList &list) {
    node *cur = list.head;
    while (cur != nullptr) {
        os << cur->data << " ";
        cur = cur->next;
    }
    os << "NULL";
    return os;
}

int SortedLinkedList::operator[](int index) {
    node *cur = this->head;
    int i = 0;
    while (cur != nullptr) {
        if (i == index) {
            return cur->data;
        }
        cur = cur->next;
        i++;
    }
    cout << "Index out of bounds" << endl;
    return -1;
}





