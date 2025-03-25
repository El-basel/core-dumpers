#include "SortedLinkedList.h"
#include <iostream>
#include <stdexcept>

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
    if (this->head == nullptr) throw std::runtime_error("The list is empty");
    node *cur = this->head;
    node *prev = nullptr;
    if (index == 0) {
        this->head = cur->next;
        delete cur;
        return;
    }
    int i = 0;
    while (cur != nullptr && i < index) {
        prev = cur;
        cur = cur->next;
        i++;
    }
    if (cur == nullptr) throw out_of_range("index out of bounds");
    prev->next = cur->next;
    delete cur;
}

ostream &operator<<(ostream &os, const SortedLinkedList &list) {
    node *cur = list.head;
    while (cur != nullptr) {
        os << cur->data << " ";
        cur = cur->next;
    }
    os << endl;
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
    throw out_of_range("index out of bounds");
}

SortedLinkedList::~SortedLinkedList() {
    node* cur = this->head;
    while(cur != nullptr){
        node* next = cur->next;
        delete cur;
        cur = next;
    }
    this->head = nullptr;
}





