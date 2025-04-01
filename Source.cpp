#include "SortingSystem.h"

// Define possible class types using std::variant
using SortingSystemVariant = variant<
        unique_ptr<SortingSystem<long long>>,    // Integers
        unique_ptr<SortingSystem<long double>>,  // Floating-Point Numbers
        unique_ptr<SortingSystem<string>>        // Text
>;

// Helper function to initialize SortingSystem
SortingSystemVariant createSortingSystem(int choice, int n)
{
    switch(choice)
    {
        case 1: return make_unique<SortingSystem<long long>>(n);
        case 2: return make_unique<SortingSystem<long double>>(n);
        case 3: return make_unique<SortingSystem<string>>(n);
    }
}

int main()
{
    int n = get_int("Enter the number of items to sort: ", 1);
    int type_choice = get_int("Select the type of data \n1) Integer \n2) Floating-Point \n3) Text \nChoose (1-3): ", 1, 3);

    // Create SortingSystem Object
    SortingSystemVariant sorter = createSortingSystem(type_choice, n);

    // Call SortingSystem::showMenu() on "sorter" using std::variant syntax
    visit([](auto& ptr) { ptr->showMenu(); }, sorter);
}
