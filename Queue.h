

#ifndef QUEUE_H
#define QUEUE_H
#include <iostream>
#include <stdexcept>
using namespace std;


template<typename T>
class Queue {
private:
    struct Node {
        T val;
        Node* next;
        Node() : next(nullptr) {}
    };
    int _size;
    Node* _front;
    Node* _back;
public:
    Queue() : _front(nullptr), _size(0) {}
    int size() {
        return _size;
    }
    T& front() {
        if (isEmpty()) {
            throw runtime_error("Queue is empty!");
        }
        return _front->val;
    }
    bool isEmpty() { return _size == 0; }
    void push(const T& val) {
        Node* newNode = new Node();
        newNode->val = val;
        if (_front == nullptr) {
            _front = newNode;
            _back = newNode;
        }
        else {
            _back->next = newNode;
            _back = newNode;
        }
        _size++;
    }

    void pop() {
        if (isEmpty()) {
            throw runtime_error("Queue is empty!");
        }
        Node* tmp;
        tmp = _front;
        if (_front == _back) {
            _front = _back = nullptr;
        }
        else {
            _front = _front->next;
        }
        delete tmp;
        _size--;
    }
    ~Queue() {
        Node* cur = _front;
        Node* tmp;
        while (cur) {
            tmp = cur;
            cur = cur->next;
            delete tmp;
        }
    }
};


#endif
