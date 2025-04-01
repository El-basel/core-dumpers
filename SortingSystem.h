#ifndef SORTINGSYSTEM_H
#define SORTINGSYSTEM_H
#include <iostream>
#include <cstdlib>
#include <variant>
#include <chrono>
#include <regex>
#include <string>
#include <sstream>
#include <fstream>
#include <filesystem>
using namespace std;

// ----------------------------------- <input and conversion helpers> -------------------------------------------//

int get_int(const string& prompt, int l = INT_MIN, int r = INT_MAX)
{
    int num;
    while (true)
    {
        try
        {
            cout << endl << prompt;
            string input; getline(cin, input, '\n');

            regex num_pattern(R"(^\s*(-?\d+(?:\.\d*)?)\s*$)");
            smatch matches;
            if (!regex_match(input, matches, num_pattern))
            {
                throw invalid_argument("Not a floating-point number or an integer");
            }

            long double num_d = stold(matches[1].str());

            if (num_d != (long long)(num_d))
            {
                cout << "Not an integer, please try again." << "\n";
                continue;
            }
            else if (num = (int)num_d; !(l <= num && num <= r))
            {
                if (l == INT_MIN && INT_MIN <= num)
                    cout << "Please enter a number that is at most " << r << "\n";
                else if (r == INT_MAX && num <= INT_MAX)
                    cout << "Please enter a number that is at least " << l << "\n";
                else
                {
                    cout << "Please enter a number from " << l << " to " << r << " inclusive." << "\n";
                    continue;
                }
            }
            else break;
        }
        catch (...)
        {
            cout << "Not a number, please try again." << "\n";
        }
    }
    return num;
}

string get_valid_text_file(const string& prompt)
{
    while (true)
    {
        cout << endl << prompt;
        string input; getline(cin, input, '\n');

        regex valid_txt_filename(R"(\s*([^.\/\\]+\.(?:txt))\s*)");
        smatch matches;
        regex_match(input, matches, valid_txt_filename);

        if (!matches[1].matched)
        {
            cout << "Please provide a valid .txt filename" << "\n";
            continue;
        }
        else if (!filesystem::exists(matches[1].str()))
        {
            cout << "`" << matches[1].str() << "` does not exist in the current directory, please provide a valid filename." << "\n";
            continue;
        }

        string filename = matches[1].str();
        ifstream input_file(filename);
        if (!input_file)
        {
            cout << "Error accessing `" << filename << "` \nProgram terminated." << endl;
            continue;
        }
        input_file.close();

        return filename;
    }
}

template<typename T>
bool attempt_conversion(const string& s, T& dest) {
    istringstream iss(s);
    return (iss >> dest) && iss.eof();
}

// ----------------------------------- </input and conversion helpers> ------------------------------------------//

template<typename T>
class SortingSystem {
private:
    T* data; // Dynamic array for storing input data
    int size; // Size of the array
    bool repeatable = true; // loop menu if console input is used, don't if reading from a file
    int counter = 0; // counter for number of iterations needed

    void reinitialize(); // rerun with new data (console-only)

    void countSortForRadix(T* arr, int size, int div); // Radix Sort Helper
    void insertionSortForBucket(T* arr, int size); // Bucket Sort Helper
    void mergeSortImplementation(int left, int right);
    void quickSortImplementation(int left, int right);

public:
    SortingSystem(int n); // Constructor
    ~SortingSystem(); // Destructor

    void insertionSort();
    void selectionSort();
    void bubbleSort();
    void shellSort();
    void mergeSort() { mergeSortImplementation(0, size - 1); }; // takes no parameters to be compatible with measureSortTime()
    void quickSort() { quickSortImplementation(0, size - 1); }; // takes no parameters to be compatible with measureSortTime()
    void countSort(); // Only for int
    void radixSort(); // Only for int
    void bucketSort();

    void merge(int left, int mid, int right); // Merge Sort Helper
    int partition(int low, int high); // Quick Sort Helper

    void displayData(); // Print the current state of the array
    void measureSortTime(void (SortingSystem::* sortFunc)());

    void showMenu(); // Display menu for user interaction
};


//--------------------------------------- <IMPLEMENTATION> ---------------------------------------//

template<typename T>
SortingSystem<T>::SortingSystem(int n)
{
    if (n <= 0)
        n = get_int("The number of items to sort must be a positive integer, Enter the number: ", 1);

    size = n;
    data = new T[size];

    int input_method = get_int("Please choose your input method (1- File, 2- Console): ", 1, 2);

    switch(input_method)
    {
        case 1:
        {
            repeatable = false;

            string filename = get_valid_text_file("Please enter the filename for the txt file containing the input data, \n"
                                                  "Data must be whitespace separated, file must contain a number of elements >= size\n"
                                                  "Extra elements will be discarded: ");
            ifstream input_file(filename);
            T temp;

            // Read exactly n elements from file
            for(int i = 0;; i++) {
                if(input_file.eof()) {
                    if(i >= size) {
                        cout << "\nRead successful\n\n";
                        break;
                    }
                    cout << "\nInsufficient data in file, Program terminated.\n\n";
                    exit(2);
                }

                input_file >> temp;

                if(input_file.fail()) {
                    if(i >= size) {
                        // Exactly n elements retrieved, no compatible/readable data left
                        cout << "\nRead successful\n\n";
                        break;
                    } else {
                        cout << "\nDatatype mismatch or filestream error\n"
                                "(Tip: ensure the file has data of the correct datatype.)\n"
                                "Program terminated.\n\n";
                        exit(2);
                    }
                } else if(i >= size) {
                    // enough data extracted, excess (readable and compatible) data remaining
                    cout << "\nRead " << size << " elements successfully. Warning: Extra data discarded\n\n";
                    break;
                }

                data[i] = temp;
            }
            input_file.close();

            break;
        }
        case 2:
        {
            for (int i = 0; i < size; i++)
            {
                while (true)
                {
                    cout << "\nEnter item " << (i + 1) << ": ";
                    string input;
                    getline(cin, input);

                    regex single_element_pattern(R"(^\s*(\S+)\s*$)");
                    smatch matches;
                    if (!regex_match(input, matches, single_element_pattern))
                    {
                        cout << "\nInvalid input. Please enter exactly one item.\n\n";
                        continue;
                    }

                    string token = matches[1].str();
                    if (attempt_conversion(token, data[i]))
                        break;
                    else
                        cout << "\nFailed to convert `" << token << "`. Ensure data is of the correct datatype.\n\n";
                }
            }
            cout << "\nRead successful\n\n";
        }
    }

    srand(time(nullptr));
}

template<typename T>
void SortingSystem<T>::reinitialize()
{
    size = get_int("Enter the number of items to sort: ", 1);
    for (int i = 0; i < size; i++)
    {
        while (true)
        {
            cout << "\nEnter item " << (i + 1) << ": ";
            string input;
            getline(cin, input);

            regex single_element_pattern(R"(^\s*(\S+)\s*$)");
            smatch matches;
            if (!regex_match(input, matches, single_element_pattern))
            {
                cout << "\nInvalid input. Please enter exactly one item.\n\n";
                continue;
            }

            string token = matches[1].str();
            if (attempt_conversion(token, data[i]))
                break;
            else
                cout << "\nFailed to convert `" << token << "`. Ensure data is of the correct datatype.\n\n";
        }
    }
    cout << "\nRead successful\n\n";
}

template<typename T>
SortingSystem<T>::~SortingSystem()
{
    delete[] data;
}

template<typename T>
void SortingSystem<T>::insertionSort()
{
    int count = 1;
    cout << "Initial Data: ";
    displayData();
    for (int i = 1, j; i < size; i++) {
        T tmp = data[i];
        bool change = false;
        for (j = i; j > 0 && data[j - 1] > tmp; j--) {
            data[j] = data[j - 1];
            change = true;
        }
        data[j] = tmp;
        if (!change) continue;
        cout << "Iteration " << count++ << ": ";
        displayData();
    }
    cout << "Sorted Data: ";
    displayData();
}

//------------------------------------------------------------------------------------------//

template<typename T>
void SortingSystem<T>::selectionSort()
{
    cout << "Initial Data: ";
    displayData();
    for (int i = 0, minIndex; i < size - 1; i++) {
        minIndex = i;
        for (int j = i + 1; j < size; j++) {
            if (data[j] < data[minIndex]) {
                minIndex = j;
            }
        }
        swap(data[i], data[minIndex]);
        cout << "Iteration " << i + 1 << ": ";
        displayData();
    }
    cout << "Sorted Data: ";
    displayData();
}

//------------------------------------------------------------------------------------------//

template<typename T>
void SortingSystem<T>::bubbleSort()
{
    cout << "Initial Data: ";
    displayData();
    for (int i = 0; i < size - 1; i++) {
        bool change = false;
        for (int j = 0; j < size - 1 - i; j++) {
            if (data[j] > data[j + 1]) {
                swap(data[j], data[j + 1]);
                change = true;
            }
        }
        if (!change) break;
        cout << "Iteration " << i + 1 << ": ";
        displayData();
    }
    cout << "Sorted Data: ";
    displayData();
}

//------------------------------------------------------------------------------------------//

template<typename T>
void SortingSystem<T>::shellSort()
{
    cout << "Initial Data: ";
    displayData();
    int count = 1;
    for (int gap = size / 2; gap > 0; gap /= 2) {
        cout << "Gap distance between indices = " << gap << "\n";
        for (int i = gap, j; i < size; i++) {
            T tmp = data[i];
            for (j = i; j >= gap && data[j - gap] > tmp; j -= gap) {
                data[j] = data[j - gap];
            }
            data[j] = tmp;
        }
        cout << "Iteration " << count++ << ": ";
        displayData();
    }
    cout << "Sorted Data: ";
    displayData();
}

//------------------------------------------------------------------------------------------//

template<typename T>
void SortingSystem<T>::merge(int left, int mid, int right)
{
    int size1 = mid - left + 1;
    int size2 = right - mid;
    T* arr1 = new T[size1];
    T* arr2 = new T[size2];
    for (int i = 0; i < size1; i++) {
        arr1[i] = data[left + i];
    }
    for (int j = 0; j < size2; j++) {
        arr2[j] = data[mid + 1 + j];
    }
    int i = 0, j = 0, k = left;
    while (i < size1 && j < size2) {
        if (arr1[i] < arr2[j]) {
            data[k++] = arr1[i++];
        }
        else {
            data[k++] = arr2[j++];
        }
    }
    while (i < size1) {
        data[k++] = arr1[i++];
    }
    while (j < size2) {
        data[k++] = arr2[j++];
    }
    cout << "Left Half: ";
    cout << "[";
    for (int i = 0; i < size1 - 1; i++) {
        cout << arr1[i] << ", ";
    }
    cout << arr1[size1 - 1] << "]\n";
    cout << "Right Half: ";
    cout << "[";
    for (int i = 0; i < size2 - 1; i++) {
        cout << arr2[i] << ", ";
    }
    cout << arr2[size2 - 1] << "]\n";
    cout << "After Merging: ";
    cout << "[";
    for (int i = left; i < k - 1; i++) {
        cout << data[i] << ", ";
    }
    cout << data[k - 1] << "]\n";

    delete[] arr1;
    delete[] arr2;
}

template<typename T>
void SortingSystem<T>::mergeSortImplementation(int left, int right)
{
    if (left >= right) return;
    if (counter == 0) {
        cout << "Initial Data: ";
        displayData();
    }
    counter++;
    int middle = (left + right) / 2;
    mergeSortImplementation(left, middle);
    mergeSortImplementation(middle + 1, right);
    merge(left, middle, right);
    if (left == 0 && right == size - 1) {
        counter = 0;
        cout << "Sorted Data: ";
        displayData();
    }
}

//------------------------------------------------------------------------------------------//

template<typename T>
int SortingSystem<T>::partition(int low, int high)
{
    int index = low + (rand() % (high - low + 1));
    swap(data[index], data[low]);
    T tmp = data[low];
    int i = low;
    for (int j = low + 1; j <= high; j++) {
        if (data[j] < tmp) {
            i++;
            swap(data[j], data[i]);
        }
    }
    swap(data[i], data[low]);
    return i;
}

template<typename T>
void SortingSystem<T>::quickSortImplementation(int left, int right)
{
    if (left >= right) return;
    if (counter == 0) {
        cout << "Initial Data: ";
        displayData();
    }
    counter++;
    int pivot_index = partition(left, right);
    quickSortImplementation(left, pivot_index - 1);
    quickSortImplementation(pivot_index + 1, right);
    cout << "Pivot: " << data[pivot_index] << " -> ";
    for (int i = 0; i < pivot_index; i++) {
        if (i == 0) {
            cout << "[";
        }
        cout << data[i];
        if (i == pivot_index - 1) {
            cout << "]";
        }
        else if (i > 0) {
            cout << ", ";
        }
    }
    cout << " " << data[pivot_index] << " ";
    for (int i = pivot_index + 1; i < size; i++) {
        if (i == pivot_index + 1) {
            cout << "[";
        }
        cout << data[i];
        if (i == size - 1) {
            cout << "]";
        }
        else if (i > pivot_index - 1) {
            cout << ", ";
        }
    }
    cout << "\n";
    if (left == 0 && right == size - 1) {
        cout << "Sorted Data: ";
        displayData();
    }
}

//------------------------------------------------------------------------------------------//

template<typename T>
void SortingSystem<T>::countSort()
{
    if constexpr (std::is_same_v<T, long long>)
    {
        if (size == 0) return;
        T min_num = data[0];
        T max_num = data[0];
        for (int i = 1; i < size; i++) {
            min_num = min(min_num, data[i]);
            max_num = max(max_num, data[i]);
        }
        int range = max_num - min_num + 1;
        int* frequency_array = new int[range]();

        cout << "Initial Data: ";
        displayData();
        for (int i = 0; i < size; i++) {
            ++frequency_array[data[i] - min_num];
        }

        cout << "Frequency Array:\n";
        for (int i = 0; i < range; i++) {
            cout << min_num + i << ": " << frequency_array[i] << "\n";
        }

        for (int i = 1; i < range; i++) {
            frequency_array[i] += frequency_array[i - 1];
        }

        cout << "Cumulative Frequency Array:\n";
        for (int i = 0; i < range; i++) {
            cout << min_num + i << ": " << frequency_array[i] << "\n";
        }

        T* sorted_data = new T[size];

        for (int i = size - 1; i >= 0; i--) {
            sorted_data[--frequency_array[data[i] - min_num]] = data[i];
        }

        cout << "Sorted Data Step by Step:\n";
        for (int i = 0; i < size; i++) {
            cout << sorted_data[i] << " ";
        }
        cout << "\n";

        for (int i = 0; i < size; i++) {
            data[i] = sorted_data[i];
        }
        cout << "Final Sorted Data: ";
        displayData();

        delete[] frequency_array;
        delete[] sorted_data;
    }
}

//------------------------------------------------------------------------------------------//

template<typename T>
void SortingSystem<T>::countSortForRadix(T* arr, int size, int div) {
    if constexpr (std::is_same_v<T, long long>)
    {
        int digits_frequency[10] = { 0 };
        // Compute Frequency of each digit
        for (int i = 0; i < size; i++) {
            int index = (arr[i] / div) % 10;
            ++digits_frequency[index];
        }

        // Print frequency array for the current digit place
        cout << "Digit Frequency for div = " << div << ":\n";
        for (int i = 0; i < 10; i++) {
            cout << i << ": " << digits_frequency[i] << " ";
        }
        cout << "\n";
        // Compute prefix sum
        for (int i = 1; i < 10; i++) {
            digits_frequency[i] += digits_frequency[i - 1];
        }

        // Sort based on digit place value
        T* sorted_data = new T[size];
        for (int i = size - 1; i >= 0; i--) {
            int digit = (arr[i] / div) % 10;
            sorted_data[--digits_frequency[digit]] = arr[i];
        }

        // Print sorted result at current digit place
        cout << "Sorted by digit place div = " << div << ": ";
        for (int i = 0; i < size; i++) {
            cout << sorted_data[i] << " ";
        }
        cout << "\n";

        for (int i = 0; i < size; i++) {
            arr[i] = sorted_data[i];
        }

        delete[] sorted_data;
    }
}


template<typename T>
void SortingSystem<T>::radixSort()
{
    if constexpr (std::is_same_v<T, long long>)
    {
        if (size == 0) return;
        cout << "Initial Data: ";
        displayData();

        // Separate negative and positive numbers
        int positive_count = 0, negative_count = 0;
        for (int i = 0; i < size; i++) {
            if (data[i] < 0) negative_count++;
            else positive_count++;
        }
        T* positive_nums = new T[positive_count];
        T* negative_nums = new T[negative_count];


        int max_positive = INT_MIN, max_negative = INT_MIN;

        int i = 0, j = 0;
        for (int k = 0; k < size; k++) {
            if (data[k] < 0) {
                if(max_negative < data[k] * -1)
                    max_negative = data[k] * -1;
                negative_nums[j++] = (data[k] * -1);  // Convert to positive for sorting
            }
            else {
                if(max_positive < data[k])
                    max_positive = data[k];
                positive_nums[i++] = data[k];
            }
        }

        cout << "\nSorting Positive Numbers:\n";
        for (int div = 1; max_positive / div > 0; div *= 10) {
            countSortForRadix(positive_nums, positive_count, div);
        }

        cout << "\nSorting Negative Numbers:\n";
        for (int div = 1; max_negative / div > 0; div *= 10) {
            countSortForRadix(negative_nums, negative_count, div);
        }
        T* sorted_data = new T[size];
        int index = 0;

        for (int k = negative_count - 1; k >= 0; k--) {
            sorted_data[index++] = (negative_nums[k] * -1);
        }

        for (int k = 0; k < positive_count; k++) {
            sorted_data[index++] = positive_nums[k];
        }

        for (int i = 0; i < size; i++) {
            data[i] = sorted_data[i];
        }

        cout << "\nFinal Sorted Data: ";
        displayData();

        delete[] negative_nums;
        delete[] positive_nums;
        delete[] sorted_data;
    }
}

//------------------------------------------------------------------------------------------//

template<typename T>
void SortingSystem<T>::insertionSortForBucket(T* arr, int size)
{
    for (int i = 1, j; i < size; i++) {
        T tmp = arr[i];
        for (j = i; j > 0 && arr[j - 1] > tmp; j--) {
            arr[j] = arr[j - 1];
        }
        arr[j] = tmp;
    }

}

template<typename T>
void SortingSystem<T>::bucketSort()
{
    if constexpr (std::is_same_v<T, int> || std::is_same_v<T, long long> || std::is_same_v<T, float> || std::is_same_v<T, double>)
    {
        if (size == 0) return;

        cout << "Initial Data: ";
        displayData();

        T min_num = data[0], max_num = data[0];
        for (int i = 1; i < size; i++) {
            min_num = min(min_num, data[i]);
            max_num = max(max_num, data[i]);
        }
        int buckets_num = size;
        T interval = (max_num - min_num + 1) / buckets_num;
        T** buckets = new T * [buckets_num];
        int* bucket_length = new int[buckets_num]();
        for (int i = 0; i < size; i++) {
            int bucket_index = (data[i] - min_num) / interval;
            if (bucket_index > buckets_num - 1) bucket_index = buckets_num - 1;
            ++bucket_length[bucket_index];
        }

        for (int i = 0; i < buckets_num; i++) {
            buckets[i] = new T[bucket_length[i]];
        }

        int* buckets_current_index = new int[buckets_num]();

        // Assign elements to buckets
        cout << "\nBucket Assignments:\n";
        for (int i = 0; i < size; i++) {
            int bucket_index = (data[i] - min_num) / interval;
            if (bucket_index > buckets_num - 1) bucket_index = buckets_num - 1;
            buckets[bucket_index][buckets_current_index[bucket_index]] = data[i];
            ++buckets_current_index[bucket_index];
            cout << "Element " << data[i] << " -> Bucket " << bucket_index + 1 << "\n";
        }

        // Print bucket contents before sorting
        cout << "\nBuckets Before Sorting:\n";
        for (int i = 0; i < buckets_num; i++) {
            cout << "Bucket " << i + 1 << ": ";
            for (int j = 0; j < bucket_length[i]; j++) {
                cout << buckets[i][j] << " ";
            }
            cout << "\n";
        }

        for (int i = 0; i < buckets_num; i++) {
            insertionSortForBucket(buckets[i], bucket_length[i]);
        }

        // Print bucket contents after sorting
        cout << "\nBuckets After Sorting:\n";
        for (int i = 0; i < buckets_num; i++) {
            cout << "Bucket " << i + 1 << ": ";
            for (int j = 0; j < bucket_length[i]; j++) {
                cout << buckets[i][j] << " ";
            }
            cout << "\n";
        }


        int index = 0;
        for (int i = 0; i < buckets_num; i++) {
            for (int j = 0; j < bucket_length[i]; j++) {
                data[index++] = buckets[i][j];
            }
        }


        for (int i = 0; i < buckets_num; i++) {
            delete[] buckets[i];
        }
        delete[] buckets;
        delete[] bucket_length;
        delete[] buckets_current_index;
    }
}

//------------------------------------------------------------------------------------------//

template<typename T>
void SortingSystem<T>::displayData()
{
    cout << "[";
    for (int i = 0; i < size - 1; i++) {
        cout << data[i] << ", ";
    }
    cout << data[size - 1] << "]\n";
}

//------------------------------------------------------------------------------------------//

template<typename T>
void SortingSystem<T>::measureSortTime(void (SortingSystem::* sortFunc)())
{
    auto start = std::chrono::steady_clock::now();
    (this->*sortFunc)();
    auto end = std::chrono::steady_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::nanoseconds>(end - start).count();
    std::cout << "\nTime taken: " << duration/((long double)1e6) << " ms" << std::endl;
}

template<typename T>
void SortingSystem<T>::showMenu()
{
    while(true)
    {

        int algo_choice;
        bool int_only = false, numeric_only = false;

        cout << "1. Insertion Sort\n" << "2. Selection Sort\n" << "3. Bubble Sort \n" << "4. Shell Sort\n" << "5. Merge Sort\n" << "6. Quick Sort\n" << "7. Count Sort\n" << "8. Radix Sort\n" << "9. Bucket Sort\n";
        algo_choice = get_int("Choose the sorting algorithm (1-9): ", 1, 9);
        if(algo_choice == 7 || algo_choice == 8) int_only = true;
        if(algo_choice == 9) numeric_only = true;

        if(int_only)
        {
            if constexpr(!std::is_same_v<T, long long>)
            {
                cout << "\nOnly integers are supported by the selected algorithm, Program Terminated.\n\n";
                exit(3);
            }
        }

        if(numeric_only)
        {
            if constexpr(!std::is_same_v<T, long long> && !std::is_same_v<T, long double>)
            {
                cout << "\nOnly numbers are supported by the selected algorithm, Program Terminated.\n\n";
                exit(3);
            }
        }

        if constexpr(!std::is_same_v<T, long long> && !std::is_same_v<T, long double> && !std::is_same_v<T, std::string>)
        {
            cout << "\nOnly integers, floating-point numbers, and text are supported, Program Terminated.\n\n";
            exit(3);
        }


        switch(algo_choice)
        {
            case 1:
                measureSortTime(&SortingSystem<T>::insertionSort);
                break;
            case 2:
                measureSortTime(&SortingSystem<T>::selectionSort);
                break;
            case 3:
                measureSortTime(&SortingSystem<T>::bubbleSort);
                break;
            case 4:
                measureSortTime(&SortingSystem<T>::shellSort);
                break;
            case 5:
                measureSortTime(&SortingSystem<T>::mergeSort);
                break;
            case 6:
                measureSortTime(&SortingSystem<T>::quickSort);
                break;
            case 7:
                measureSortTime(&SortingSystem<T>::countSort);
                break;
            case 8:
                measureSortTime(&SortingSystem<T>::radixSort);
                break;
            case 9:
                measureSortTime(&SortingSystem<T>::bucketSort);
                break;
        }

        displayData();

        if(!repeatable)
        {
            cout << "Thanks for using our program!\n";
            exit(0);
        }

        bool quit = get_int("Do you want to rerun with new data (console-only)? \n0- Yes, continue \n1- No, quit. \nChoose (0/1): ", 0, 1);
        if(quit)
        {
            cout << "\nThanks for using our program!\n";
            exit(0);
        }
        else
            reinitialize();
    }
}

//--------------------------------------- </IMPLEMENTATION> ---------------------------------------//


#endif
