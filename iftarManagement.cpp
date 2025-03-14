#include <iostream>
#include <string_view>
class Guest {
private:
    std::string name;
    std::string contact;
    std::string iftar_date;
public:
    Guest() = default;
    Guest(std::string p_name, std::string p_contact, std::string p_iftar_date)
            : name{p_name}, contact{p_contact}, iftar_date{p_iftar_date} {}
    Guest(Guest& guest) {
        if(this == &guest) {
            return;
        }
        this->name = guest.name;
        this->contact = guest.contact;
        this->iftar_date = guest.iftar_date;
    }

    void display_guest() {
        std::cout << "Guest: " << name << ", Contact: " << contact
                  << ", Iftar Date: " << iftar_date << std::endl;
    }
    std::string_view get_name() {
        return name;
    }

    void update_invitation(std::string new_date) {iftar_date = new_date;}
    bool operator<(Guest& right_operand) {
        for (int i = 0; i < iftar_date.length(); i++) {
            if(iftar_date[i] < right_operand.iftar_date[i]) {
                return true;
            }
        }
        return false;
    }
};

void merge(Guest* arr, Guest* leftArr, Guest* rightArr,
           int left, int middle, int right) {
    int i = 0, j = 0, k = 0;
    while(i < middle && j < (right - middle)) {
        if(leftArr[i] < rightArr[j]) {
            arr[k++] = leftArr[i++];
        } else {
            arr[k++] = rightArr[j++];
        }
    }
    while(i < middle) {
        arr[k++] = leftArr[i++];
    }
    while(j < (right - middle)) {
        arr[k++] = rightArr[j++];
    }
}

void mergeSort(Guest* arr, int left, int right) {
    if((right - left) <= 1) return;
    int middle = (left + right) / 2;
    Guest* leftArr = new Guest[middle];
    Guest* rightArr = new Guest[right - middle];
    for (int i = 0; i < middle; ++i) {
        leftArr[i] = arr[i];
    }
    for(int i = 0; i < right - middle; ++i) {
        rightArr[i] = arr[middle + i];
    }
    mergeSort(leftArr, 0, middle);
    mergeSort(rightArr, 0, right - middle);
    merge(arr, leftArr, rightArr, left, middle, right);
    delete[] leftArr;
    delete[] rightArr;
}


class iftarManager {
private:
    Guest* guest_list = nullptr;
    int length = 0;
public:
    void add_guest(Guest& guest) {
        if(length == 0) {
            guest_list = new Guest(guest);
            ++length;
        } else {
            Guest* tmp = new Guest[length + 1];
            for (int i = 0; i < length; ++i) {
                tmp[i] = guest_list[i];
            }
            tmp[length] = guest;
            if(length == 1) {
                delete guest_list;
            } else {
                delete[] guest_list;
            }
            guest_list = tmp;
            ++length;
        }
    }
    void display_all_guests() {
        for (int i = 0; i < length; ++i) {
            guest_list[i].display_guest();
        }
    }
    void update_guest_inviation(std::string name, std::string new_date) {
        for (int i = 0; i < length; ++i) {
            if(guest_list[i].get_name() == name) {
                guest_list[i].update_invitation(new_date);
            }
        }
    }
    void send_reminder() {

    }

    void sort_guest_list() {
        mergeSort(guest_list, 0, length);
    }
    ~iftarManager() {
        if(length == 1) {
            delete guest_list;
        } else if(length > 1) {
            delete[] guest_list;
        }
    }
};

int main() {
    Guest guest1 = Guest("Aisha", "aisha@example.com", "2025-03-15");
    Guest guest2 = Guest("Omar", "omar@example.com", "2025-03-18");
    Guest guest3 = Guest("Zainab", "zainab@example.com", "2025-03-20");
    iftarManager manager;
    manager.add_guest(guest1);
    manager.add_guest(guest2);
    manager.add_guest(guest3);
    manager.display_all_guests();
    manager.sort_guest_list();
    manager.display_all_guests();

    return 0;
}