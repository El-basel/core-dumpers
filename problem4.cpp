#include <iostream>
#include <fstream>
#include <optional>
#include <algorithm>
class Patient {
public:
    std::string name;
    int severity;
    int arrival_time;
    bool operator<(Patient& p) {
        if(this->severity < p.severity) {
            return true;
        } else if(this->severity == p.severity && this->arrival_time > p.arrival_time) {
            return true;
        }
        return false;
    }
    bool operator>(Patient& p) {
        if(this->severity > p.severity) {
            return true;
        } else if(this->severity == p.severity && this->arrival_time < p.arrival_time) {
            return true;
        }
        return false;
    }
    Patient() = default;
    Patient(std::string p_name, int p_severity, int p_arrival_time) :
    name{p_name}, severity{p_severity}, arrival_time{p_arrival_time} {}
    friend std::ostream& operator<<(std::ostream& out, Patient p) {
        out << "Treating: " << p.name << ", Severity: " <<
        p.severity << ", Arrival Time: " << p.arrival_time;
        return out;
    }
};

class Priority_Queue {
private:
    Patient* patients = nullptr;
    int length = 0;
    void max_heapify(int low, int high) {
        Patient tmp = patients[low];
        int largest = 2 * low + 1;
        while(largest <= high) {
            if(largest < high) {
                if(patients[largest] < patients[largest + 1]) {
                    ++largest;
                }
            }
            if(tmp > patients[largest]) {
                break;
            } else {
                std::swap(patients[low], patients[largest]);
                low = largest;
                largest = 2 * low + 1;
            }
        }
        patients[low] = tmp;
    }
public:
    void insert(Patient p) {
        if(length == 0) {
            patients = new Patient[1];
            patients[0] = p;
            ++length;
        } else {
            Patient* tmp = new Patient[++length];
            for (int i = 0; i < length - 1; ++i) {
                tmp[i] = patients[i];
            }
            tmp[length - 1] = p;
            delete[] patients;
            patients = tmp;
            for(int i = length/2 - 1; i >= 0; i--) {
                max_heapify(i, length - 1);
            }
        }
    }

    std::optional<Patient> extract_max() {
        if(length > 0) {
            Patient p = patients[0];
            patients[0] = patients[--length];
            max_heapify(0, length - 1);
            return p;
        }
        return std::nullopt;
    }
    std::optional<Patient> peek() {
        if(length > 0) {
            Patient p = patients[0];
            return p;
        }
        return std::nullopt;
    }
    void print_heap() {
        for (int i = 0; i < length; ++i) {
            std::cout << patients[i] << '\n';
        }
    }
    void heapsort() {
        while(length > 0) {
            std::optional<Patient> p = extract_max();
            if(p) {
                std::cout << *p << std::endl;
            }
        }
    }
    ~Priority_Queue() {
        delete[] patients;
    }
};
int main() {
    std::fstream file;
    std::string fileName;
    std::cout << "Enter file name: ";
    std::cin >> fileName;
    file.open(fileName);
    if(!file) {
        std::cerr << "File not found\n";
        return 0;
    }
    Patient p;
    std::string input;
    Priority_Queue emergency;
    while(!file.eof()) {
        file >> input;
        std::transform(input.begin(),input.end(), input.begin(),[] (unsigned  char c) { return std::tolower(c);});
        p.name = input;
        file >> input;
        p.severity = atoi(input.c_str());
        file >> input;
        p.arrival_time = atoi(input.c_str());
        emergency.insert(p);
    }
    emergency.print_heap();
    std::cout << "-------------------------------------\n";
    emergency.heapsort();
}