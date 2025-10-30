#include <queue>
#include <vector>
#include <iostream>
using namespace std;

template <class Comparable>
class BinaryHeap {
    int size;          // Maximum size of the heap
    int currentSize;   // Current num of elements in the heap
    Comparable* array; // Array to store heap elements

    void percolateUp(int hole) {
        Comparable temp = move(array[hole]);
        while (hole > 0 && temp < array[(hole - 1) / 2]) {
            array[hole] = move(array[(hole - 1) / 2]);
            hole = (hole - 1) / 2;
        }
        array[hole] = std::move(temp);
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

    void insert(Comparable&& x) {
        if (currentSize == size) {
            throw overflow_error("Heap is full");
        }
        int hole = currentSize++;
        array[hole] = std::move(x);
        percolateUp(hole);
    }

    void buildHeap(Comparable* elements, int n) {
        if (n > size) {
            throw overflow_error("Heap size exceeded");
        }
        currentSize = n;
        for (int i = 0; i < n; ++i) {
            array[i] = std::move(elements[i]);
        }

        for (int i = (currentSize - 2) / 2; i >= 0; --i) {
            percolateDown(i);
        }
    }

    vector<Comparable> findNodesLessThan(Comparable X) const {
        vector<Comparable> result;
        if (currentSize == 0) {
            return result;
        }

        queue<int> indices;
        indices.push(0);

        while (!indices.empty()) {
            int index = indices.front();
            indices.pop();

            // Process the current node
            if (array[index] < X) {
                result.push_back(array[index]);

                // Push children if they exist
                int leftChild = 2 * index + 1;
                int rightChild = 2 * index + 2;

                if (leftChild < currentSize) {
                    indices.push(leftChild);
                }
                if (rightChild < currentSize) {
                    indices.push(rightChild);
                }
            }
        }

        return result;
    }

    void printHeap() const {
        for (int i = 0; i < currentSize; ++i) {
            cout << array[i] << " ";
        }
        cout << endl;
    }

    void printLessX (Comparable X, int i=0) {
        if (i > currentSize || array[i] >= X) {
            return ;
        } else {
            cout << array[i] << endl;
            printLessX(X, 2*i+1);
            printLessX(X, 2*i+2);
        }
    }
};

int main () 
{

}

// we use a vector of boolean named possible answers in order to avoid comparaison with childs 
