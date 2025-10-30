#include <iostream>
#include <chrono>  

using namespace std;

template <class Comparable>
class BinaryHeap {
    int size;          // Maximum size
    int currentSize;   // Current elements in the heap
    Comparable* array; // Array to store heap elements

    void percolateUp(int hole) {
        Comparable temp = move(array[hole]);
        while (hole > 0 && temp < array[(hole - 1) / 2]) { 
            array[hole] = move(array[(hole - 1) / 2]); 
            hole = (hole - 1) / 2; 
        }
        array[hole] = move(temp);
    }

    void percolateDown(int hole) {
        Comparable temp = move(array[hole]);
        int child;
        while ((hole * 2 + 1) < currentSize) {
            child = hole * 2 + 1; // Left child
            if (child + 1 < currentSize && array[child + 1] < array[child]) {
                child++; // Right child is smaller
            }
            if (array[child] < temp) {
                array[hole] = move(array[child]);
                hole = child;
            } else {
                break;
            }
        }
        array[hole] = move(temp);
    }

public:
    BinaryHeap(int size) : size(size), currentSize(0) {
        array = new Comparable[this->size];
    }

    ~BinaryHeap() {
        delete[] array;
    }

    // Insert one element
    void insert(Comparable&& x) {
        if (currentSize == size) {
            throw overflow_error("Heap is full");
        }
        int hole = currentSize++;
        array[hole] = move(x);
        percolateUp(hole);
    }

    // Build the heap in linear time
    void buildHeap(Comparable* elements, int n) {
        if (n > size) {
            throw overflow_error("Heap size exceeded");
        }
        currentSize = n;
        for (int i = 0; i < n; ++i) {
            array[i] = move(elements[i]);
        }

        // Percolate down from the first non-leaf node
        for (int i = (currentSize - 2) / 2; i >= 0; --i) {
            percolateDown(i);
        }
    }

    void deleteMin( Comparable & minItem )
    {
        minItem = move( array[0] );
        array[0] = move( array[ currentSize-- ] );
        percolateDown(0);
    }

    void printHeap() const {
        for (int i = 0; i < currentSize; ++i) {
            cout << array[i] << " ";
        }
        cout << endl;
    }
};

template <typename T>
void measureHeapPerformance(T* elements, int n) {
    BinaryHeap<T> heap(n);

    auto startInsert = chrono::high_resolution_clock::now();
    for (int i = 0; i < n; ++i) {
        heap.insert(std::move(elements[i]));
    }
    auto endInsert = chrono::high_resolution_clock::now();
    chrono::duration<double> insertTime = endInsert - startInsert;

    heap = BinaryHeap<T>(n); // Reset heap
    auto startBuild = chrono::high_resolution_clock::now();
    heap.buildHeap(elements, n);
    auto endBuild = chrono::high_resolution_clock::now();
    chrono::duration<double> buildTime = endBuild - startBuild;

    cout << "Insertion Time: " << insertTime.count() << " seconds\n";
    cout << "BuildHeap Time: " << buildTime.count() << " seconds\n";
}

int main() {
    const int N = 100000;

    // Allocate arrays for test cases
    int* sortedElements = new int[N];
    int* reverseElements = new int[N];
    int* randomElements = new int[N];

    // Generate test cases
    for (int i = 0; i < N; ++i) {
        sortedElements[i] = i + 1;
        reverseElements[i] = N - i;
        randomElements[i] = i + 1;
    }

    // Shuffle the random input
    for (int i=0; i<N; ++i) {
        swap(randomElements[i], randomElements[rand()%N]);
    }

    cout << "Testing Sorted Input:\n";
    measureHeapPerformance(sortedElements, N);
    delete[] sortedElements;

    cout << "\nTesting Reverse-Ordered Input:\n";
    measureHeapPerformance(reverseElements, N);
    delete[] reverseElements;

    cout << "\nTesting Random Input:\n";
    measureHeapPerformance(randomElements, N);
    delete[] randomElements;

    return 0;
}
