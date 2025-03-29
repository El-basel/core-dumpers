#include <iostream>
#include <string_view>
#include "iftarManagement.h"


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

Guest::Guest(std::string p_name, std::string p_contact, std::string p_iftar_date)
        : name{p_name}, contact{p_contact}, iftar_date{p_iftar_date} {}
Guest::Guest(Guest& guest) {
    if(this == &guest) {
        return;
    }
    this->name = guest.name;
    this->contact = guest.contact;
    this->iftar_date = guest.iftar_date;
}

void Guest::display_guest() {
    std::cout << "Guest: " << name << ", Contact: " << contact
              << ", Iftar Date: " << iftar_date << std::endl;
}
std::string_view Guest::get_name() {
    return name;
}
std::string_view Guest::get_date() {
    return iftar_date;
}

void Guest::update_invitation(std::string new_date) {iftar_date = new_date;}
bool Guest::operator<(Guest& right_operand) {
    for (int i = 0; i < iftar_date.length(); i++) {
        if(iftar_date[i] < right_operand.iftar_date[i]) {
            return true;
        }
    }
    return false;
}

void iftarManager::add_guest(Guest& guest) {
    if(length == 0) {
        guest_list = new Guest[1];
        guest_list[0] = guest;
        ++length;
    } else {
        Guest* tmp = new Guest[length + 1];
        for (int i = 0; i < length; ++i) {
            tmp[i] = guest_list[i];
        }
        tmp[length] = guest;
        delete[] guest_list;
        guest_list = tmp;
        ++length;
    }
}
void iftarManager::display_all_guests() {
    for (int i = 0; i < length; ++i) {
        guest_list[i].display_guest();
    }
}
void iftarManager::update_guest_invitation(std::string name, std::string new_date) {
    for (int i = 0; i < length; ++i) {
        if(guest_list[i].get_name() == name) {
            guest_list[i].update_invitation(new_date);
        }
    }
}
void iftarManager::send_reminder() {
    for (int i = 0; i < length; ++i) {
        std::cout << "Reminder sent to " << guest_list[i].get_name()
        << ": Your iftar invitation is on " << guest_list[i].get_date() << std::endl;
    }
}
void iftarManager::sort_guest_list() {
    mergeSort(guest_list, 0, length);
}

void iftarManager::remove_guest(std::string name) {
    int new_length = length;
    std::string lowercase;
    for (int i = 0; i < name.length(); ++i) {
        name[i] = std::tolower(name[i]);
    }
    for (int i = 0; i < length; ++i) {
        lowercase = guest_list[i].get_name();
        for (int k = 0; k < guest_list[i].get_name().length(); ++k) {
            lowercase[k] =  std::tolower(guest_list[i].get_name()[k]);
        }
        if(lowercase == name) {
            --new_length;
        }
    }
    Guest* new_list = new Guest[new_length];
    for (int i = 0,j = 0; i < length; ++i) {
        lowercase = guest_list[i].get_name();
        for (int k = 0; k < guest_list[i].get_name().length(); ++k) {
            lowercase[k] =  std::tolower(guest_list[i].get_name()[k]);
        }
        if(lowercase == name) {
            continue;
        }
        new_list[j] = guest_list[i];
        ++j;
    }
    delete[] guest_list;
    length = new_length;
    guest_list = new_list;
}
iftarManager::~iftarManager() {
    delete[] guest_list;
}


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
    manager.send_reminder();
    manager.remove_guest("omar");
    manager.display_all_guests();

    return 0;
}