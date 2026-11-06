#include <iostream>
#include <vector>
#include <random>
#include <chrono>
#include <algorithm>
#include <cassert>

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

void QuickSort(std::vector<int> &arr, int low, int high) {
    // Base case
    if (high <= low) {
        return;
    }

    int pivotIndex = Partition(arr, low, high);

    // left subarray recursive call
    QuickSort(arr, low, pivotIndex - 1);

    // right subarray recursive call
    QuickSort(arr, pivotIndex + 1, high);
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

void CountingSortTagged(std::vector<std::pair<int, char>>& arr, int k) {
    // Initialize count array
    std::vector<int> count;

    for (int i = 0; i < k + 1; i++) {
        count.push_back(0);
    }

    // Count frequencies using integer keys
    for (size_t i = 0; i < arr.size(); i++) {
        int desired_index = arr[i].first;
        count[desired_index]++;
    }

    // Calculate cumulative counts
    for (int i = 1; i <= k; i++) {
        count[i] += count[i - 1];
    }

    // Create output array of pairs
    std::vector<std::pair<int, char>> output(arr.size());

    // Stable placement from right to left
    for (int i = static_cast<int>(arr.size()) - 1; i >= 0; i--) {
        int position = count[arr[i].first] - 1;
        output[position] = arr[i];
        count[arr[i].first]--;
    }

    // Copy sorted records back
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

bool validSorted(std::vector<int> &arr) {
    for (size_t i = 0; i < arr.size() - 1; i++) {
        if (!(arr[i] <= arr[i + 1])) {
            return false;
        }
    }

    return true;
}

void TestMeInsertionSort(std::vector<int> arr) {
    std::vector<int> expected(arr);
    std::vector<int> insertionArr(arr);

    std::sort(expected.begin(), expected.end());
    InsertionSort(insertionArr);

    std::cout << "Insertion Sort result: ";
    for (int num : insertionArr) {
        std::cout << num << " ";
    }
    std::cout << "\n";

    assert(insertionArr == expected);
    std::cout << "Insertion Sort test PASSED!\n";
}

void TestMeQuickSort(std::vector<int> arr) {
    std::vector<int> expected(arr);
    std::vector<int> quickArr(arr);

    std::sort(expected.begin(), expected.end());
    QuickSort(quickArr, 0, static_cast<int>(quickArr.size()) - 1);

    std::cout << "Quick Sort result: ";
    for (int num : quickArr) {
        std::cout << num << " ";
    }
    std::cout << "\n";

    assert(quickArr == expected);
    std::cout << "Quick Sort test PASSED!\n";
}

void TestMeCountingSort(std::vector<int> arr, int k) {
    std::vector<int> expected(arr);
    std::vector<int> countingArr(arr);

    std::sort(expected.begin(), expected.end());
    CountingSort(countingArr, k);

    std::cout << "Counting Sort result: ";
    for (int num : countingArr) {
        std::cout << num << " ";
    }
    std::cout << "\n";

    assert(countingArr == expected);
    std::cout << "Counting Sort test PASSED!\n";
}

void TestCountingSortStability() {
    std::vector<std::pair<int, char>> records = {
        {2, 'a'},
        {1, 'b'},
        {2, 'c'},
        {1, 'd'}
    };

    std::vector<std::pair<int, char>> expected = {
        {1, 'b'},
        {1, 'd'},
        {2, 'a'},
        {2, 'c'}
    };

    CountingSortTagged(records, 2);

    std::cout << "Tagged Counting Sort result: ";

    for (const auto& record : records) {
        std::cout << "(" << record.first << ","
                  << record.second << ") ";
    }

    std::cout << "\n";

    assert(records == expected);
    std::cout << "Counting Sort stability test PASSED!\n";
}

void WarmUp() {
    std::vector<int> practice = {5, 2, 8, 1, 4};
    std::vector<int> insertionSortPracArray(practice);
    std::vector<int> quickSortPracArray(practice);
    std::vector<int> countingSortPracArray(practice);

    InsertionSort(insertionSortPracArray);
    QuickSort(quickSortPracArray, 0, static_cast<int>(quickSortPracArray.size() - 1));
    CountingSort(countingSortPracArray, 8);
}

double GetMedian(std::vector<double> &arr) {
    std::sort(arr.begin(), arr.end());
    // If the array has even length
    if (arr.size() % 2 == 0) {
        return (arr[(arr.size() / 2)] + arr[(arr.size() / 2) - 1]) / 2;
    } else { // If array has odd length
        return arr[(arr.size() / 2)];
    }
}

int main() {
    WarmUp();

    std::vector<int> sizes = {
        10, 100, 1000, 2000, 5000, 10000, 20000
    };
    
    for (int n : sizes) {
        for (int multiplier : {1, 100}) {
            int k = n * multiplier;

            std::cout << "TESTING FOR N = " << n
                    << ", K = " << k << "\n";

            std::vector<double> insertionTimes;
            std::vector<double> quickTimes;
            std::vector<double> countingTimes;

            for (int i = 0; i < 5; i++) {
                std::vector<int> randomArray = GenerateRandomArray(n, k);
                
                std::vector<int> expected(randomArray);
                std::sort(expected.begin(), expected.end());

                std::vector<int> insertionArray(randomArray);
                std::vector<int> quickArray(randomArray);
                std::vector<int> countingArray(randomArray);

                std::cout << "TRIAL " << (i + 1) << "\n";
                
                /**
                 * INSERTION SORT
                 */
                auto start = std::chrono::steady_clock::now();
                InsertionSort(insertionArray);
                auto end = std::chrono::steady_clock::now();

                std::chrono::duration<double, std::milli> elapsed = end - start;
                std::cout << "Insertion sort time: " << elapsed.count() << "\n";
                insertionTimes.push_back(elapsed.count());

                /**
                 * QUICK SORT
                 */

                start = std::chrono::steady_clock::now();
                QuickSort(quickArray, 0, static_cast<int>(quickArray.size() - 1));
                end = std::chrono::steady_clock::now();

                elapsed = end - start;
                std::cout << "Quick sort time: " << elapsed.count() << "\n";
                quickTimes.push_back(elapsed.count());

                /**
                 * COUNTING SORT
                 */

                start = std::chrono::steady_clock::now();
                CountingSort(countingArray, k);
                end = std::chrono::steady_clock::now();

                elapsed = end - start;
                std::cout << "Counting sort time: " << elapsed.count() << "\n";
                countingTimes.push_back(elapsed.count());

                assert(insertionArray == expected);
                assert(quickArray == expected);
                assert(countingArray == expected);
                
                std::cout << "\n";
            }
            std::cout << "MEDIAN FOR INSERTION : " << GetMedian(insertionTimes) << "\n";
            std::cout << "MEDIAN FOR QUICK : " << GetMedian(quickTimes) << "\n";
            std::cout << "MEDIAN FOR COUNTING : " << GetMedian(countingTimes) << "\n"; 
            std::cout << "------------------------------------------\n";    
        }
    }

    return 0;
}