#include "SortingSystem.h"
#include <string>

int data_type_menu() {
    do {
        cout << "What is The Data type of your data?\n";
        cout << "[1] Int\n[2] Long Long\n[3] FLoat\n[4] Double\n[5] String\n[6] Char\n";
        cout << "Enter your Choice: ";
        int choice = valid_int();
        if (choice > 0 && choice < 7) {
            return choice;
        }
        else {
            cout << "Invalid Choice!\n";
        }
    } while (true);
}

void user_menu() {
    do {
        cout << "How do you want to enter the data?\n";
        cout << "[1] From Console\n[2] From File\n";
        cout << "Enter your choice: ";
        int choice = valid_int();
        if (choice == 1) {
            do {
                int data_type = data_type_menu();
                int size = 0;
                do {
                    cout << "Enter the number of items to sort: ";
                    size = valid_int();
                    if (size > 0) {
                        break;
                    }
                    else {
                        cout << "Invliad Input!\n";
                    }
                } while (true);
                if (data_type == 1) {
                    SortingSystem<int> sorter(size);
                    sorter.showMenu();
                }
                else if (data_type == 2) {
                    SortingSystem<long long> sorter(size);
                    sorter.showMenu();
                }
                else if (data_type == 3) {
                    SortingSystem<float> sorter(size);
                    sorter.showMenu();
                }
                else if (data_type == 4) {
                    SortingSystem<double> sorter(size);
                    sorter.showMenu();
                }
                else if (data_type == 5) {
                    SortingSystem<string> sorter(size);
                    sorter.showMenu();
                }
                else {
                    SortingSystem<char> sorter(size);
                    sorter.showMenu();
                }
                cout << "Do you want to sort another dataset? (y/n): ";
                string ans; cin >> ans;
                if (ans == "n") {
                    cout << "Thank you for using the sorting system! Goodbye!\n";
                    break;
                }
                cin.clear();
            } while (true);
            break;
        }

        else if (choice == 2) {
            string filename;
            cout << "enter file name without extensions : ";
            cin >> filename;
            filename += ".txt";
            cin.clear();
            ifstream file(filename);
            if (!file) {
                cout << "Error opening file\n";
                return;
            }
            string line;
            while (getline(file, line)) {

                int data_type = stoi(line);
                if (!getline(file, line)) break;
                int size = stoi(line);

                if (!getline(file, line)) break;

                stringstream ss(line);

                bool valid = true;

                if (data_type == 1) { // Integer
                    int temp;
                    int* data = new int[size];
                    for (int i = 0; i < size; i++) {
                        if (!(ss >> temp)) {
                            cout << "Invalid integer found in file!" << "\n";
                            return;
                        }                        
                        data[i] = temp;
                        
                    }
                    if (valid) {
                        SortingSystem<int> sorter(size);
                        if (!getline(file, line)) break;
                        int sort_algo = stoi(line);
                        if (sort_algo < 1 || sort_algo > 9) {
                            cout << "Invalid sorting algorithm choice!\n";
                            return;
                        }
                        sorter.inputData(data, sort_algo);
                    }
                    delete[] data;
                }
                else if (data_type == 2) { // Long long
                    long long temp;
                    long long* data = new long long[size];
                    for (int i = 0; i < size; i++) {
                        if (!(ss >> temp)) {
                            cout << "Invalid long long found in file!" << "\n";
                            return;
                        }
                        data[i] = temp;

                    }
                    if (valid) {
                        SortingSystem<long long> sorter(size);
                        if (!getline(file, line)) break;
                        int sort_algo = stoi(line);
                        if (sort_algo < 1 || sort_algo > 9) {
                            cout << "Invalid sorting algorithm choice!\n";
                            return;
                        }
                        sorter.inputData(data, sort_algo);

                    }
                    delete[] data;
                }
                else if (data_type == 3) { // Float
                    float temp;
                    float* data = new float[size];
                    for (int i = 0; i < size; i++) {
                        if (!(ss >> temp)) {
                            cout << "Invalid floating-point number found in file!"<< "\n";
                            return;
                        }
                        data[i] = temp;                       
                    }
                    if (valid) {
                        SortingSystem<float> sorter(size);
                        if (!getline(file, line)) break;
                        int sort_algo = stoi(line);
                        if (sort_algo < 1 || sort_algo > 9) {
                            cout << "Invalid sorting algorithm choice!\n";
                            return;
                        }
                        sorter.inputData(data, sort_algo);

                    }
                    delete[] data;
                }
                else if (data_type == 4) { // Double
                    double temp;
                    double* data = new double[size];
                    for (int i = 0; i < size; i++) {
                        if (!(ss >> temp)) {
                            cout << "Invalid floating-point number found in file!" << "\n";
                            return;
                        }
                            data[i] = temp;
                    }
                    if (valid) {
                        SortingSystem<double> sorter(size);
                        if (!getline(file, line)) break;
                        int sort_algo = stoi(line);
                      
                        if (sort_algo < 1 || sort_algo > 9) {
                            cout << "Invalid sorting algorithm choice!\n";
                            return;
                        }
                        sorter.inputData(data, sort_algo);
                    }
                    delete[] data;
                }
                else if (data_type == 5) { // String
                    string* data = new string[size];
                    for (int i = 0; i < size; i++) {
                        if (!(ss >> data[i])) {
                            valid = false;
                            break;
                        }
                    }
                    if (valid) {
                        SortingSystem<string> sorter(size);
                        if (!getline(file, line)) break;
                        int sort_algo = stoi(line);
                        if (sort_algo < 1 || sort_algo > 9) {
                            cout << "Invalid sorting algorithm choice!\n";
                            return;
                        }
                        sorter.inputData(data, sort_algo);
                    }
                    delete[] data;
                }
                else if (data_type == 6) { // Char
                    char* data = new char[size];
                    string temp;
                    for (int i = 0; i < size; i++) {
                        if (!(ss >> temp)) {
                            valid = false;
                            break;
                        }
                        if (temp.size() > 1) {
                            cout << "Invalid Char found in file: " << temp << "\n";
                            return;
                        }
                        data[i] = temp[0];
                    }
                    if (valid) {
                        SortingSystem<char> sorter(size);
                        if (!getline(file, line)) break;
                        int sort_algo = stoi(line);
                        if (sort_algo < 1 || sort_algo > 9) {
                            cout << "Invalid sorting algorithm choice!\n";
                            return;
                        }
                        sorter.inputData(data, sort_algo);
                    }
                    delete[] data;
                }
                else {
                    cout << "Invalid data type in file.\n";
                    return;
                }

                cout << "\n-----------------------------------------------------------------------------\n";
                
            }
            file.close();
            break;
        }
        else {
            cout << "Invalid Choice!\n";
        }
    }while (true);
}

int main()
{
    user_menu();
}