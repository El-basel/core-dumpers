#ifndef SORTINGSYSTEM_H
#define SORTINGSYSTEM_H
#include <iostream>
#include <cstdlib>
#include <chrono>
#include <string>
#include <sstream>
#include <fstream>
#include <iomanip>

using namespace std;
int valid_int() {
    int choice; cin >> choice;
    if (cin.fail() || cin.peek() != '\n') {
        cin.clear(); // Clear the error flag
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        return -1;
    }
    return choice;
}


template<typename T>
class SortingSystem {
private:
    T* data; // Dynamic array for storing input data
    int size; // Size of the array
    int counter = 0; // counter for number of iterations needed

    void countSortForRadix(T* arr, int size, long long div); // Radix Sort Helper
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
    void inputData(T* arr,int algo_num);  // takes the input from file 
};


//--------------------------------------- <IMPLEMENTATION> ---------------------------------------//

template<typename T>
SortingSystem<T>::SortingSystem(int n)
{
    size = n;
    data = new T[size];
    srand(time(nullptr));
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
        else{
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
    if constexpr (std::is_same_v<T, int> || std::is_same_v<T, long long>)
    {
        if (size == 0) return;
        T min_num = data[0];
        T max_num = data[0];
        for (int i = 1; i < size; i++) {
            min_num = min(min_num, data[i]);
            max_num = max(max_num, data[i]);
        }
        int range = max_num - min_num + 1;
        long long* frequency_array = new long long[range]();

        cout << "Initial Data: ";
        displayData();
        for (int i = 0; i < size; i++) {
            ++frequency_array[data[i] - min_num];
        }

        cout << "Frequency Array:\n";
        for (int i = 0; i < range; i++) {
            if (i % 5 == 0) cout << "\n";
            cout << min_num + i << ": " << frequency_array[i] << "  ";
        }
        cout << "\n";
        for (int i = 1; i < range; i++) {
            frequency_array[i] += frequency_array[i - 1];
        }

        cout << "Cumulative Frequency Array:\n";
        for (int i = 0; i < range; i++) {
            if (i % 5 == 0) cout << "\n";
            cout << min_num + i << ": " << frequency_array[i] << "  ";
        }
        cout << "\n";
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
void SortingSystem<T>::countSortForRadix(T* arr, int size, long long div) {
    if constexpr (std::is_same_v<T, int> || std::is_same_v<T, long long>)
    {
        long long digits_frequency[10] = { 0 };
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
    if constexpr (std::is_same_v<T, int> || std::is_same_v<T, long long>)
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


        long long max_positive = 0, max_negative = 0;

        int i = 0, j = 0;
        for (int k = 0; k < size; k++) {
            if (data[k] < 0) {
                if (data[k] * -1 > max_negative) max_negative = data[k] * -1;
                negative_nums[j++] = (data[k] * -1);  // Convert to positive for sorting
            }
            else {
                if (data[k] > max_positive) max_positive = data[k];
                positive_nums[i++] = data[k];
            }
        }
        cout << "\nSorting Positive Numbers:\n";
        for (long long div = 1; max_positive / div > 0; div *= 10) {
            countSortForRadix(positive_nums, positive_count, div);
        }

        cout << "\nSorting Negative Numbers:\n";
        for (long long div = 1; max_negative / div > 0; div *= 10) {
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

        cout << "\nFinal Sorted Data: ";
        displayData();

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
    using milliseconds = std::chrono::duration<long long, std::milli>;
    auto start = std::chrono::steady_clock::now();
    (this->*sortFunc)();
    auto end = std::chrono::steady_clock::now();
    auto duration = (std::chrono::duration_cast<milliseconds>(end - start)).count();
    cout << fixed << setprecision(6);
    cout << "\nSorting Time: " << (duration < 1.0 ? "<" : "") << duration / 1e6 << " seconds\n";
}

//------------------------------------------------------------------------------------------//
template<typename T>
void SortingSystem<T>::inputData(T* arr, int algo_num)
{
    for (int i = 0; i < size; i++) {
        data[i] = arr[i];
    }
    switch (algo_num)
    {
    case 1:
        cout << "\nSorting using Insertion Sort...\n";
        measureSortTime(&SortingSystem<T>::insertionSort);
        break;
    case 2:
        cout << "\nSorting using Selection Sort...\n";
        measureSortTime(&SortingSystem<T>::selectionSort);
        break;
    case 3:
        cout << "\nSorting using Bubble Sort...\n";
        measureSortTime(&SortingSystem<T>::bubbleSort);
        break;
    case 4:
        cout << "\nSorting using Shell Sort...\n";
        measureSortTime(&SortingSystem<T>::shellSort);
        break;
    case 5:
        cout << "\nSorting using Merge Sort...\n";
        measureSortTime(&SortingSystem<T>::mergeSort);
        break;
    case 6:
        cout << "\nSorting using Quick Sort...\n";
        measureSortTime(&SortingSystem<T>::quickSort);
        break;
    case 7:
        cout << "\nSorting using Count Sort...\n";
        measureSortTime(&SortingSystem<T>::countSort);
        break;
    case 8:
        cout << "\nSorting using Radix Sort...\n";
        measureSortTime(&SortingSystem<T>::radixSort);
        break;
    case 9:
        cout << "\nSorting using Bucket Sort...\n";
        measureSortTime(&SortingSystem<T>::bucketSort);
        break;
    }
}

//------------------------------------------------------------------------------------------//
template<typename T>
void SortingSystem<T>::showMenu()
{
    cout << "\n\n";
 
    for (int i = 0; i < size; i++) {
        cout << "Enter Data " << i + 1 << ": ";
        cin >> data[i];
        if (cin.fail() || cin.peek() != '\n') {
            cin.clear(); // Clear the error flag
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Error: Your input doesn't match the data type you chose!\n";
            return;
        }
    }
    int algo_choice;
    bool int_only = false;
    cin.clear();
    do {
        cout << "\n\n";
        cout << "Select a sorting algorithm:\n";
        cout << "[1] Insertion Sort\n"
            << "[2] Selection Sort\n"
            << "[3] Bubble Sort\n"
            << "[4] Shell Sort\n"
            << "[5] Merge Sort\n"
            << "[6] Quick Sort\n"
            << "[7] Count Sort (Only for integers)\n"
            << "[8] Radix Sort (Only for integers)\n"
            << "[9] Bucket Sort (Only for numbers (int - long long - float - double) )\n";
        cout << "Choose the sorting algorithm(1-9): ";
        algo_choice = valid_int();
        if (algo_choice < 1 || algo_choice > 9) {
            cout << "Invalid Choice!\n";
        }
        else {
            break;
        }
    } while (true);
    if (algo_choice == 7 || algo_choice == 8) int_only = true;

    if (int_only)
    {
        if constexpr (!std::is_same_v<T, int> && !std::is_same_v<T, long long>)
        {
            cout << "\nOnly integer types (int, long long) are supported by the selected algorithm, Program Terminated.\n\n";
            exit(3);
        }
    }
    else
    {
        if constexpr (std::is_same_v<T, char> || std::is_same_v<T, std::string> )
        {
            if (algo_choice == 9) {
                cout << "\nOnly Numbers (int - long long - float - double) are supported by Bucket Sort ALgorithm, Program Terminated.\n\n";
                exit(3);
            }
        }
    }

    switch (algo_choice)
    {
    case 1:
        cout << "\nSorting using Insertion Sort...\n";
        measureSortTime(&SortingSystem<T>::insertionSort);
        break;
    case 2:
        cout << "\nSorting using Selection Sort...\n";
        measureSortTime(&SortingSystem<T>::selectionSort);
        break;
    case 3:
        cout << "\nSorting using Bubble Sort...\n";
        measureSortTime(&SortingSystem<T>::bubbleSort);
        break;
    case 4:
        cout << "\nSorting using Shell Sort...\n";
        measureSortTime(&SortingSystem<T>::shellSort);
        break;
    case 5:
        cout << "\nSorting using Merge Sort...\n";
        measureSortTime(&SortingSystem<T>::mergeSort);
        break;
    case 6:
        cout << "\nSorting using Quick Sort...\n";
        measureSortTime(&SortingSystem<T>::quickSort);
        break;
    case 7:
        cout << "\nSorting using Count Sort...\n";
        measureSortTime(&SortingSystem<T>::countSort);
        break;
    case 8:
        cout << "\nSorting using Radix Sort...\n";
        measureSortTime(&SortingSystem<T>::radixSort);
        break;
    case 9:
        cout << "\nSorting using Bucket Sort...\n";
        measureSortTime(&SortingSystem<T>::bucketSort);
        break;
    }
    

    
}

//--------------------------------------- </IMPLEMENTATION> ---------------------------------------//


#endif 

