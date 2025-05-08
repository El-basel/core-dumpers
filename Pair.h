#ifndef PAIR_H
#define PAIR_H
#include <iostream>
using namespace std;

template<typename T1,typename T2>
class Pair{
private:
    T1 first;
    T2 second;
public:
    Pair()= default;
    Pair(T1 first, T2 second){
        this->first = first;
        this->second = second;
    }
    T1 getFirst() {return first;}
    T2 getSecond() {return second;}
    bool operator ==(const Pair& other) const{
        return this->first == other.first;
    }
    bool operator<(const Pair& other) const{
        return this->first < other.first;
    }
    bool operator>(const Pair& other) const{
        return this->first > other.first;
    }

    Pair& operator=(const Pair& other){
        if (this != &other) {
            first = other.first;
            second = other.second;
        }
        return *this;
    }
    template<typename U1, typename U2>
    friend ostream& operator<<(ostream& out, const Pair<U1, U2>& pair);

};

template<typename T1, typename T2>
ostream& operator<<(ostream& out, const Pair<T1, T2>& pair) {
    out << "[ID: " << pair.first << ", ";
    out << pair.second << "]\n";
    return out;
}


#endif
