
#ifndef DYNAMICARRAY_H
#define DYNAMICARRAY_H
#include <iostream>
using namespace std;
template <typename T>
class DynamicArray{
private:
    T* data;
    int _size;
    int _capacity;
public:
    DynamicArray(){
        _capacity = 1;
        data = new T[_capacity];
        _size = 0;
    }
    DynamicArray(int n){
        _capacity = n * 2;
        data = new T[_capacity];
        _size = n;
        for (int i = 0; i < _size; ++i) {
            data[i] = T(); // default-initialize each element
        }
    }
    ~DynamicArray(){
        delete[] data;
    }
    int size() {
        return _size;
    }
    int capacity(){
        return _capacity;
    }
    T& operator[](int index) {
        if(index < 0 || index >= _size)
            throw out_of_range("Index out of range!");
        return data[index];
    }

    void push(const T& item){
      if( size()  == capacity()){
          _capacity *= 2;
          T* newData = new T[_capacity];
          for(int i = 0; i < size();i++){
              newData[i] = data[i];
          }
          delete[] data;
          data = newData;
      }
      data[_size++] = item;
    }
    bool isEmpty(){ return _size == 0;}
    void pop(){
        if(isEmpty()){
            throw runtime_error("Dynamic Array is Empty!");
        }
        _size--;
    }
    T& front(){
        if(isEmpty()){
            throw runtime_error("Dynamic Array is Empty!");
        }
        return data[0];
    }
    T& back(){
        if(isEmpty()){
            throw runtime_error("Dynamic Array is Empty!");
        }
        return data[_size - 1];
    }
    void clear(){
      _size = 0;
    }
    DynamicArray(const DynamicArray& other){ // copy constructor
        _capacity = other._capacity;
        _size = other._size;
        data = new T[_capacity];
        for(int i = 0; i < _size; i++){
            data[i] = other.data[i];
        }
    }
    DynamicArray& operator=(const DynamicArray& other) { // copy assignment
        if (this == &other) {
            return *this; // Handle self-assignment
        }
        delete[] data;
        _capacity = other._capacity;
        _size = other._size;
        data = new T[_capacity];
        for (int i = 0; i < _size; ++i) {
            data[i] = other.data[i];
        }

        return *this;
    }

};
#endif
