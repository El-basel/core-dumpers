
#ifndef ADDRESSBOOK_H
#define ADDRESSBOOK_H

#include <iostream>
#include <string>
#include <regex>
#include <limits>
#include <fstream>
#include <sstream>
#include "AVLTree.h"
#include "DynamicArray.h"
#include "Dictionary.h"
#include "Pair.h"
using namespace std;
class AddressBook{
private:
    int valid_int() {
        int choice; cin >> choice;
        if (cin.fail() || cin.peek() != '\n') {
            cin.clear(); // Clear the error flag
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            return -1;
        }
        return choice;
    }
    int printOptions(){
        do {
            cout << "[1] Add New Contact\n"
                 << "[2] Search for Contact\n"
                 << "[3] Delete Contact\n"
                 << "[4] List All Contacts (Sorted by ID)\n"
                 << "[5] Display Current Tree Structure\n"
                 << "[6] Back\n";
            cout << "\nEnter Operation (1-6): ";
            int choice = valid_int();
            if(choice > 0 && choice < 7){
                return choice;
            }
            else {
                cout << "Invalid Choice!\n";
            }
        }while(true);
    }
    void userMenu(){
        AVLTree<Pair<int, Dictionary>> tree;
        do{
            int op = printOptions();
            if(op == 1){
                cout << "Enter unique ID (positive integer): ";
                int id = valid_int();
                if(id < 1){
                    cout  << "Invalid ID\n";
                    continue;
                }
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                cout  << "Enter name: ";
                string name;
                getline(cin, name);
                cout << "Your Phone must be like the following format: 000-0000-0000\n";
                string phone;
                cout << "Enter Phone: ";
                getline(cin,phone);
                regex phonePattern(R"(^\d{3}-\d{4}-\d{4}$)");
                if(!regex_match(phone,phonePattern)){
                    cout << "Invalid Phone Format!\n";
                    continue;
                }
                cout << "Your Email must be like the following format: example@gmail.com\n";
                cout << "Enter Email: ";
                string email;
                getline(cin,email);
                regex emailPattern("^[a-zA-Z0-9._%+-]+@[a-zA-Z]+\\.[a-zA-Z]{2,}$");
                if(!regex_match(email,emailPattern)){
                    cout << "Invalid Email Format!\n";
                    continue;
                }
                // Search for an existing node
                Pair<int, Dictionary> searchKey(id, Dictionary(name, phone, email));
                Pair<int, Dictionary> foundNode(0, Dictionary("", "", ""));
                if (tree.getNode(searchKey, foundNode)) {
                    cout << "\nError: Contact with ID " << id << " already exists!\n";
                }
                else {
                    tree.insertNode(searchKey);
                    cout << "\nContact added successfully.\n";
                }
                cout << "\n" << string(90, '-') << "\n\n";
            }
            if(op == 2){
                cout << "Enter ID to search (positive integer): ";
                int id = valid_int();
                if(id < 1){
                    cout  << "Invalid ID\n";
                    continue;
                }
                Pair<int, Dictionary> searchKey(id, Dictionary("", "", ""));
                Pair<int, Dictionary> foundNode(0, Dictionary("", "", ""));

                if (tree.getNode(searchKey, foundNode)) {
                    cout << "C\nontact Found\n";
                    cout << foundNode;
                }
                else {
                    cout << "\nContact with ID " << id << " Not Found!\n";
                    
                }
                cout << "\n" << string(90, '-') << "\n\n";
            }
            if(op == 3){
                cout << "Enter ID to delete: ";
                int id = valid_int();
                if(id < 1){
                    cout  << "Invalid ID\n";
                    continue;
                }
                if(tree.deleteNode(Pair<int, Dictionary>(id, Dictionary("", "", "")))){
                    cout << "Contact deleted successfully.\n";
                }
                else{
                    cout << "Contact not Found!\n";
                    
                }
                cout << "\n" << string(90, '-') << "\n\n";
            }
            if (op == 4){

                if (tree.isEmpty()) {
                    cout << "Address Book is empty.\n";
                    
                }
                else {
                    cout << "Contacts in Address Book (sorted by ID):\n\n";
                    tree.inOrder(tree.getroot());
                }
                cout << "\n" << string(90, '-') << "\n\n";
            }
            if(op == 5){
                if (tree.isEmpty()) {
                    cout << "Address Book is empty.\n";
                   
                }
                else {
                    cout << "Current AVL Tree:\n";
                    tree.printTree();
                }
                cout << "\n" << string(90, '-') << "\n\n";
            }
            if(op == 6){
                break;
            }
        } while (true);

    }
   
    void fileInput() {
        string filename;
        cout << "Enter file name without extension: ";
        cin >> filename;
        filename += ".txt";
        ifstream file(filename);
        if (!file) {
            cout << "Error opening file: " << filename << "\n";
            return;
        }

        AVLTree<Pair<int, Dictionary>> tree;
        string line;

        while (getline(file, line)) {
            stringstream ss(line);
            int op;
            if (!(ss >> op)) {
                cout << "Invalid operation!\n";
                break;
            }

            if (op == 1) {
                int id;
                string name, phone, email;

                if (!getline(file, line) || !(stringstream(line) >> id) || id < 1) {
                    cout << "Invalid or missing ID\n";
                    break;
                }

                if (!getline(file, name)) {
                    cout << "Missing name\n";
                    break;
                }

                if (!getline(file, phone)) {
                    cout << "Missing phone\n";
                    break;
                }

                if (!getline(file, email)) {
                    cout << "Missing email\n";
                    break;
                }

                regex phonePattern(R"(^\d{3}-\d{4}-\d{4}$)");
                if (!regex_match(phone, phonePattern)) {
                    cout << "Invalid Phone Format!\n";
                    break;
                }

                regex emailPattern(R"(^[a-zA-Z0-9._%+-]+@[a-zA-Z]+\.[a-zA-Z]{2,}$)");
                if (!regex_match(email, emailPattern)) {
                    cout << "Invalid Email Format!\n";
                    break;
                }

                Pair<int, Dictionary> searchKey(id, Dictionary(name, phone, email));
                Pair<int, Dictionary> foundNode(0, Dictionary("", "", ""));
                if (tree.getNode(searchKey, foundNode)) {
                    cout << "Error: Contact with ID " << id << " already exists!\n";
                }
                else {
                    tree.insertNode(searchKey);
                    cout << "Contact added successfully.\n";
                }
                cout << "\n" << string(90, '-') << "\n\n";
            }

            else if (op == 2 || op == 3) {
                int id;
                if (!getline(file, line) || !(stringstream(line) >> id) || id < 1) {
                    cout << "Invalid ID\n";
                    break;
                }

                if (op == 2) {
                    Pair<int, Dictionary> searchKey(id, Dictionary("", "", ""));
                    Pair<int, Dictionary> foundNode(0, Dictionary("", "", ""));
                    if (tree.getNode(searchKey, foundNode)) {
                        cout << "Contact Found\n";
                        cout << foundNode;
                    }
                    else {
                        cout << "\nContact with ID " << id << " Not Found!\n";
                    }
                    cout << "\n" << string(90, '-') << "\n\n";
                }

                if (op == 3) {
                    if (tree.deleteNode(Pair<int, Dictionary>(id, Dictionary("", "", "")))) {
                        cout << "Contact deleted successfully.\n";
                    }
                    else {
                        cout << "Contact not found\n";
                    }
                    cout << "\n" << string(90, '-') << "\n\n";
                }
            }

            else if (op == 4) {

                if (tree.isEmpty()) {                   
                        cout << "Address Book is empty.\n";
                        
                }

                else {
                    cout << "Contacts in Address Book (sorted by ID):\n\n";
                    tree.inOrder(tree.getroot());
                }
               
                cout << "\n" << string(90, '-') << "\n\n";
            }

            else if (op == 5) {
                if (tree.isEmpty()) {
                    cout << "Address Book is empty.\n";
                    
                }
                else {
                    cout << "Current AVL Tree:\n";
                    tree.printTree();
                }
               
                cout << "\n" << string(90, '-') << "\n\n";
            }

            else if (op == 6) {
                cout << "Exiting " <<  filename <<"\n\n";
                break;
            }

            else {
                cout << "Invalid operation code: " << op << endl;
                break;
            }
        }

        file.close();
    }


public:
    AddressBook()= default;

    void runProgram(){
        do{
            cout << string(90, '-') << "\n";
            cout << string(35, ' ') << "Address Book Application" << "\n";
            cout << string(90, '-') << "\n";
            cout << "\n\nHow do you want to enter the Data?\n"
                 << "[1] From Console\n"
                 << "[2] From File\n"
                 << "[3] Exit Program\n";
            cout << "\nEnter your Choice: ";
            int choice = valid_int();
            if(choice == 1){
                userMenu();
            }
            else if(choice == 2){
                fileInput();
            }
            else if (choice == 3){
                cout << "Thanks For Using Our Program (:\n";
                break;
            }
            else{
                cout << "Invalid Choice!\n";
            }
        }while(true);
    }
};
#endif
