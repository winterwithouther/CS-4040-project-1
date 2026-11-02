#include <iostream>
#include <vector>
#include <random>
#include <chrono>

void InsertionSort(std::vector<int>& arr) {
    /**
     * We begin the loop at 1, assuming the first
     * element is already sorted.
     */
    for (size_t i = 1; i < arr.size(); i++) {
        /**
         * key refers to the element we are going to 
         * insert in to the sorted subarray.
         */
        int key = arr[i];

        /**
         * m helps us shift elements in the subarray
         * based on the comparision with key
         */
        int m = i;

        /**
         * sorting the subarray
         */
        while (m > 0 && arr[m - 1] > key) {
            /**
             * Shift our elements to the right if
             * our key element is less than the current
             * element we are comparing.
             */
            arr[m] = arr[m - 1];
            m--;
        }

        /**
         * Insert the key at its correct position
         * after shifting all larger elements.
         */
        arr[m] = key;
    }
}

int Partition(std::vector<int> &arr, int low, int high) {
    /**
     * Generating a psuedo random integer from low to high inclusive
     */
    static std::mt19937 rng(std::random_device{}());
    std::uniform_int_distribution<int> dist(low, high);
    int pivotIndex = dist(rng);

    /**
     * Swapping the last element with our pivot
     */
    int temp = arr[high];
    arr[high] = arr[pivotIndex];
    arr[pivotIndex] = temp;

    int i = low;

    for (int j = low; j < high; j++) {
        /**
         * Checking if our pivot is greater than the current element
         * we are comparing, we make sure they are placed in the left
         * subarray.
         */
        if (arr[high] > arr[j]) {
            int temp = arr[j];
            arr[j] = arr[i];
            arr[i] = temp;
            i++;
        }
    }

    /**
     * Swapping pivot back
     */
    temp = arr[high];
    arr[high] = arr[i];
    arr[i] = temp;

    return i;
}

void Quicksort(std::vector<int> &arr, int low, int high) {
    // Base case
    if (high <= low) {
        return;
    }

    int pivotIndex = Partition(arr, low, high);

    // left subarray recursive call
    Quicksort(arr, low, pivotIndex - 1);

    // right subarray recursive call
    Quicksort(arr, pivotIndex + 1, high);
}

void CountingSort(std::vector<int> &arr, int k) {
    // Initializing the count array
    std::vector<int> count;

    // Populating the count array
    for (int i = 0; i < k + 1; i++) {
        count.push_back(0);
    }

    /**
     * Counting the frequencies
     */
    for (size_t i = 0; i < arr.size(); i++) {
        int desired_index = arr[i];
        count[desired_index] = count[desired_index] + 1;
    }

    /**
     * Calculating the cumulative counts
     */
    for (int i = 1; i <= k; i++) {
        count[i] = count[i] + count[i - 1];
    }

    /**
     * Initializing the output array
     */
    std::vector<int> output;
    for (size_t i = 0; i < arr.size(); i++) {
        output.push_back(0);
    }

    /**
     * Placing elements in sorted order
     */
    for (int i = arr.size() - 1; i >= 0; i--) {
        int position = count[arr[i]] - 1;
        output[position] = arr[i];
        count[arr[i]] = count[arr[i]] - 1;
    }

    /**
     * Copying the sorted output onto the original array
     */
    for (size_t i = 0; i < arr.size(); i++) {
        arr[i] = output[i];
    }
}

std::vector<int> GenerateRandomArray(int size, int k) {
    static std::mt19937 rng(std::random_device{}());
    std::uniform_int_distribution<int> dist(0, k);

    std::vector<int> arr;

    for (int i = 0; i < size; i++) {
        int randomGeneratedInteger = dist(rng);
        arr.push_back(randomGeneratedInteger);
    }

    return arr;
}

int main() {
    std::vector<int> randomArray = GenerateRandomArray(10, 100);
    std::vector<int> insertionArr(randomArray);
    std::vector<int> quickArray(randomArray);
    std::vector<int> countingArr(randomArray);

    std::cout << "Unsorted array: ";
    for (int num : insertionArr) {
        std::cout << num << " ";
    }
    std::cout << "\n";

    auto start = std::chrono::steady_clock::now();
    InsertionSort(insertionArr);
    auto end = std::chrono::steady_clock::now();

    std::cout << "Sorted array: ";
    for (int num : insertionArr) {
        std::cout << num << " ";
    }

    std::chrono::duration<double, std::milli> elapsed = end - start;
    std::cout << "\n" << elapsed.count() << " ms" << std::endl;
    
    std::cout << std::endl;
    return 0;
}