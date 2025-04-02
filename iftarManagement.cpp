#include <iostream>
#include <string_view>
#include <regex>
#include <algorithm>
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
Guest& Guest::operator=(const Guest& guest) = default;

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
        else if(iftar_date[i] > right_operand.iftar_date[i]) {
            return false;
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
void iftarManager::send_reminder(std::string date) {
    for (int i = 0; i < length; ++i) {
        if(guest_list[i].get_date() == date) {
            std::cout << "Reminder sent to " << guest_list[i].get_name()
            << ": Your iftar invitation is on " << guest_list[i].get_date() << std::endl;
        }
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

int validateChoice(std::string choice) {
    if(choice.length() == 1) {
        int choiceInt = std::atoi(choice.c_str());
        if(choiceInt != 0) {
            return choiceInt;
        }
    }
    return 0;
}

bool validDate(std::string date) {
    std::regex regex("^\\d{4}-(0[1-9]|1[0-2])-(0[1-9]|[12]\\d|3[01])$");
    std::smatch match{};
    if(std::regex_search(date, match, regex)) {
        return true;
    }
    return false;
}

void add_guest(iftarManager& manager) {
    std::string name, contact, date;
    std::cout << "Enter guest name: ";
    std::cin >> name;
    std::transform(name.begin(), name.end(), name.begin(), [] (unsigned  char c) { return std::tolower(c);});
    std::cout << "Enter guest's contact info: ";
    std::cin >> contact;
    std::cout << "Enter guest's invitation date: ";
    std::cin >> date;
    if(!validDate(date)) {
        std::cerr << "Invalid date (precede the month and day with 0 if they are formed form single digit)\n";
        return;
    }
    Guest guest (name, contact, date);
    manager.add_guest(guest);
}

void remove_guest(iftarManager& manager) {
    std::string name;
    std::cout << "Enter guest name: ";
    std::cin >> name;
    std::transform(name.begin(), name.end(), name.begin(), [] (unsigned  char c) { return std::tolower(c);});
    manager.remove_guest(name);
}

void update_guest_invitation(iftarManager& manager) {
    std::string name, date;
    std::cout << "Enter guest name: ";
    std::cin >> name;
    std::transform(name.begin(), name.end(), name.begin(), [] (unsigned  char c) { return std::tolower(c);});
    std::cout << "Enter guest's invitation date: ";
    std::cin >> date;
    if(!validDate(date)) {
        std::cerr << "Invalid date\n";
        return;
    }
    manager.update_guest_invitation(name, date);
}

void send_reminder(iftarManager& manager) {
    std::string date;
    std::cout << "Enter invitation date: ";
    std::cin >> date;
    if(!validDate(date)) {
        std::cerr << "Invalid date\n";
        return;
    }
    manager.send_reminder(date);
}

int main() {
    std::cout << "|--------------------------|\n";
    std::cout << "| Welcome to Iftar Manager |\n";
    std::cout << "|--------------------------|\n";
    std::string choice;
    int choiceInt = 0;
    iftarManager manager;
    std::cout << "1. Use Provided Tests\n";
    std::cout << "2. Use Program Manually (enter names and dates by yourself)\n";
    std::cout << "Enter your choice: ";
    std::cin >> choice;
    choiceInt = validateChoice(choice);
    if(choiceInt == 1) {
        Guest guest1 = Guest("aisha", "aisha@example.com", "2025-03-15");
        Guest guest2 = Guest("omar", "omar@example.com", "2025-03-18");
        Guest guest3 = Guest("zainab", "zainab@example.com", "2025-03-20");

        manager.add_guest(guest1);
        manager.add_guest(guest3);
        manager.add_guest(guest2);
        manager.display_all_guests();
        std::cout << "----------\n";
        std::cout << "After sort\n";
        std::cout << "----------\n";
        manager.sort_guest_list();
        manager.display_all_guests();
        manager.update_guest_invitation("omar", "2025-03-15");
        manager.send_reminder("2025-03-15");
        manager.remove_guest("omar");
        manager.display_all_guests();
    } else if(choiceInt == 2) {
        while (true) {
            std::cout << "1. Add Guest\n";
            std::cout << "2. Remove Guest\n";
            std::cout << "3. Update Guest Invitation\n";
            std::cout << "4. Display Guests\n";
            std::cout << "5. Sort Guests\n";
            std::cout << "6. Send Reminder\n";
            std::cout << "7. Exit Program\n";
            std::cout << "Enter your choice: ";
            std::getline(std::cin >> std::ws, choice);
            choiceInt = validateChoice(choice);
            switch(choiceInt) {
                case 1:
                    add_guest(manager);
                    break;
                case 2:
                    remove_guest(manager);
                    break;
                case 3:
                    update_guest_invitation(manager);
                    break;
                case 4:
                    manager.display_all_guests();
                    break;
                case 5:
                    manager.sort_guest_list();
                    break;
                case 6:
                    send_reminder(manager);
                    break;
                case 7:
                    return 0;
                default:
                    std::cerr << "Please enter a valid choice\n";
            }
        }
    } else {
        std::cerr << "Please enter a valid choice\n";
    }
    return 0;
}