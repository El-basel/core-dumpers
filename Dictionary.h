
#ifndef DICTIONARY_H
#define DICTIONARY_H
#include <iostream>
using namespace std;
class Dictionary{
private:
    string name;
    string phone;
    string email;
public:
    Dictionary()= default;
    Dictionary(string name,string phone,string email){
        this->name = name;
        this->phone = phone;
        this->email = email;
    }
    string getName()  { return name;}
    string getPhone()  { return phone;}
    string getEmail()  { return email;}

    friend ostream& operator<<(ostream& out,const Dictionary& dictionary);
};

ostream &operator<<(ostream &out, const Dictionary &dictionary) {
    out << "Name: " << dictionary.name << ", ";
    out << "Phone: " << dictionary.phone << ", ";
    out << "Email: " << dictionary.email;
    return out;
}

#endif
