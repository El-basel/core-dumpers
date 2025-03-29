#ifndef CORE_DUMPERS_IFTARMANAGEMENT_H
#define CORE_DUMPERS_IFTARMANAGEMENT_H
#include <string>
class Guest {
private:
    std::string name;
    std::string contact;
    std::string iftar_date;
public:
    Guest() = default;
    Guest(std::string p_name, std::string p_contact, std::string p_iftar_date);
    Guest(Guest& guest);
    void display_guest();
    std::string_view get_name();
    std::string_view get_date();
    void update_invitation(std::string new_date);
    bool operator<(Guest& right_operand);
};

class iftarManager{
private:
    Guest* guest_list = nullptr;
    int length = 0;
public:
    void add_guest(Guest& guest);
    void display_all_guests();
    void update_guest_invitation(std::string name, std::string new_date);
    void send_reminder();
    void sort_guest_list();
    void remove_guest(std::string name);
    ~iftarManager();
};
#endif //CORE_DUMPERS_IFTARMANAGEMENT_H
