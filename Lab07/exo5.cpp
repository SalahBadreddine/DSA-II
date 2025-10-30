#include <iostream>
#include <vector>
#include <algorithm>
#include <ctime>
#include <chrono>
#include <random>

using namespace std;
using namespace chrono;

// Sorting Algorithms
void bubbleSort(vector<int>& arr) {
    int n = arr.size();
    for (int i = 0; i < n - 1; ++i) {
        for (int j = 0; j < n - i - 1; ++j) {
            if (arr[j] > arr[j + 1]) {
                swap(arr[j], arr[j + 1]); 
            }
        }
    }
}

void selectionSort(vector<int>& arr) {
    int n = arr.size();
    for (int i = 0; i < n - 1; ++i) {
        int minIdx = i;
        for (int j = i + 1; j < n; ++j) {
            if (arr[j] < arr[minIdx]) {
                minIdx = j;
            }
        }
        swap(arr[i], arr[minIdx]);
    }
}

void countingSort(vector<int>& arr) {
    int maxVal = *max_element(arr.begin(), arr.end());
    vector<int> count(maxVal + 1, 0);
    for (int num : arr) {
        count[num]++;
    }
    int idx = 0;
    for (int i = 0; i <= maxVal; ++i) {
        while (count[i]--) {
            arr[idx++] = i;
        }
    }
}

void insertionSort(vector<int>& arr) {
    int n = arr.size();
    for (int i = 1; i < n; ++i) {
        int key = arr[i];
        int j = i - 1;
        while (j >= 0 && arr[j] > key) {
            arr[j + 1] = arr[j];
            --j;
        }
        arr[j + 1] = key;
    }
}

void heapify(vector<int>& arr, int n, int i) {
    int largest = i;
    int left = 2 * i + 1;
    int right = 2 * i + 2;

    if (left < n && arr[left] > arr[largest]) {
        largest = left;
    }
    if (right < n && arr[right] > arr[largest]) {
        largest = right;
    }
    if (largest != i) {
        swap(arr[i], arr[largest]);
        heapify(arr, n, largest);
    }
}

void heapSort(vector<int>& arr) {
    int n = arr.size();
    for (int i = n / 2 - 1; i >= 0; --i) {
        heapify(arr, n, i);
    }
    for (int i = n - 1; i > 0; --i) {
        swap(arr[0], arr[i]);
        heapify(arr, i, 0);
    }
}

void merge(vector<int>& arr, int left, int mid, int right) {
    vector<int> leftArr(arr.begin() + left, arr.begin() + mid + 1);
    vector<int> rightArr(arr.begin() + mid + 1, arr.begin() + right + 1);
    int i = 0, j = 0, k = left;

    while (i < leftArr.size() && j < rightArr.size()) {
        if (leftArr[i] <= rightArr[j]) {
            arr[k++] = leftArr[i++];
        } else {
            arr[k++] = rightArr[j++];
        }
    }

    while (i < leftArr.size()) {
        arr[k++] = leftArr[i++];
    }
    while (j < rightArr.size()) {
        arr[k++] = rightArr[j++];
    }
}

void mergeSort(vector<int>& arr, int left, int right) {
    if (left < right) {
        int mid = left + (right - left) / 2;
        mergeSort(arr, left, mid);
        mergeSort(arr, mid + 1, right);
        merge(arr, left, mid, right);
    }
}

int partition(vector<int>& arr, int low, int high) {
    int pivot = arr[high];
    int i = low - 1;

    for (int j = low; j < high; ++j) {
        if (arr[j] < pivot) {
            ++i;
            swap(arr[i], arr[j]);
        }
    }
    swap(arr[i + 1], arr[high]);
    return i + 1;
}

void quickSort(vector<int>& arr, int low, int high) {
    if (low < high) {
        int pi = partition(arr, low, high);
        quickSort(arr, low, pi - 1);
        quickSort(arr, pi + 1, high);
    }
}


// Measure execution time
template <typename Func>
double measureTime(Func sortFunction, vector<int> arr) {
    auto start = high_resolution_clock::now();
    sortFunction(arr);
    auto end = high_resolution_clock::now();
    return duration<double, milli>(end - start).count();
}

// Generate input arrays
vector<int> generateArray(int n, string type = "random") {
    vector<int> arr(n);
    if (type == "sorted") {
        iota(arr.begin(), arr.end(), 1);
    } else if (type == "reversed") {
        iota(arr.rbegin(), arr.rend(), 1);
    } else { // random
        random_device rd;
        mt19937 gen(rd());
        uniform_int_distribution<> dist(1, 100000);
        generate(arr.begin(), arr.end(), [&]() { return dist(gen); });
    }
    return arr;
}

// Main function
int main() {
    vector<int> sizes = {1000, 10000, 100000};
    vector<string> inputTypes = {"sorted", "reversed", "random"};
    vector<pair<string, function<void(vector<int>&)>>> algorithms = {
        {"Bubble Sort", bubbleSort},
        {"Selection Sort", selectionSort},
        {"Counting Sort", countingSort},
        {"Insertion Sort", insertionSort},
        {"Heap Sort", heapSort},
        {"Merge Sort", [](vector<int>& arr) { mergeSort(arr, 0, arr.size() - 1); }},
        {"Quick Sort", [](vector<int>& arr) { quickSort(arr, 0, arr.size() - 1); }}
    };

    for (const string& type : inputTypes) {
        cout << "\nInput type: " << type << "\n";
        for (int size : sizes) {
            cout << "Array size: " << size << "\n";
            for (const auto& algo : algorithms) {
                vector<int> arr = generateArray(size, type);
                double timeTaken = measureTime(algo.second, arr);
                cout << algo.first << ": " << timeTaken << " ms\n";
            }
        }
    }

    return 0;
}

// g++ -std=c++11 exo5.cpp -o exo5 && ./exo5

/*
Output:
Input type: sorted
Array size: 1000
Bubble Sort: 3.20658 ms
Selection Sort: 2.81604 ms
Counting Sort: 0.06275 ms
Insertion Sort: 0.009292 ms
Heap Sort: 0.304 ms
Merge Sort: 1.65704 ms
Quick Sort: 4.27762 ms
Array size: 10000
Bubble Sort: 137.599 ms
Selection Sort: 117.046 ms
Counting Sort: 0.261334 ms
Insertion Sort: 0.037208 ms
Heap Sort: 1.44546 ms
Merge Sort: 7.81692 ms
Quick Sort: 206.805 ms
Array size: 100000
Bubble Sort: 11749.7 ms
Selection Sort: 11517.6 ms
Counting Sort: 2.67937 ms
Insertion Sort: 0.417834 ms
Heap Sort: 18.1433 ms
Merge Sort: 78.7707 ms
Quick Sort: 20337 ms

Input type: reversed
Array size: 1000
Bubble Sort: 2.39942 ms
Selection Sort: 1.26404 ms
Counting Sort: 0.03375 ms
Insertion Sort: 1.53188 ms
Heap Sort: 0.116417 ms
Merge Sort: 0.776042 ms
Quick Sort: 1.51225 ms
Array size: 10000
Bubble Sort: 241.014 ms
Selection Sort: 123.548 ms
Counting Sort: 0.292 ms
Insertion Sort: 150.617 ms
Heap Sort: 1.39079 ms
Merge Sort: 7.83104 ms
Quick Sort: 151.647 ms
Array size: 100000
Bubble Sort: 24768.5 ms
Selection Sort: 12457.7 ms
Counting Sort: 2.57121 ms
Insertion Sort: 15814.5 ms
Heap Sort: 17.4295 ms
Merge Sort: 78.7042 ms
Quick Sort: 15575.5 ms

Input type: random
Array size: 1000
Bubble Sort: 2.79183 ms
Selection Sort: 1.27596 ms
Counting Sort: 1.27642 ms
Insertion Sort: 0.788375 ms
Heap Sort: 0.132125 ms
Merge Sort: 0.767875 ms
Quick Sort: 0.076959 ms
Array size: 10000
Bubble Sort: 317.705 ms
Selection Sort: 119.463 ms
Counting Sort: 1.47554 ms
Insertion Sort: 77.3714 ms
Heap Sort: 1.75162 ms
Merge Sort: 8.5975 ms
Quick Sort: 0.96975 ms
Array size: 100000
Bubble Sort: 33737.6 ms
Selection Sort: 11881 ms
Counting Sort: 3.46 ms
Insertion Sort: 7901.68 ms
Heap Sort: 22.5717 ms
Merge Sort: 87.8255 ms
Quick Sort: 12.6384 ms
*/ 