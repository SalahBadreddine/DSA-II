#ifndef LIST_ARRAY_H
#define LIST_ARRAY_H


class listArray {
private:
    int* array; // dynamic array
    const int max; // we define the maximum size at the beginning 
public:
    listArray (const int& max_size) : max(max_size) {
        this->array = new int [max+1];
        array[0] = 0;
    }

    ~listArray () {
        delete [] array ;
    }

    // We store the current size in the first index
    int currentSize() {
        return array[0];
    }

    // Add at the beginning O(n)
    void push_front(const int& element) {
        int n = currentSize();
        if (n < this->max) {
            for (int i=n+1; i>1; i--) {
                array[i] = array[i-1];
            }
            array[1] = element;
            array[0]++;
        }
    } 

    // Add at the end O(1)
    void push_back(const int& element) {
        int n = currentSize();
        if (n < this->max) {
            array[n+1] = element;
            array[0]++;
        }
    }

    // Add at the kth position O(n-k) -> O(n)
    void push(const int& element, int k) {
        int n = currentSize();
        if (n < this->max) {
            for (int i=n+1; i>k; i--) {
                array[i] = array[i-1];
            }
            array[k] = element;
            array[0]++ ;
        }
    }

    // Deleting an element at the beginning O(n)
    int pop_front() {
        int n = currentSize();
        int temp = array[1];
        for (int i=1; i<n; i++) {
            array[i] = array[i+1];
        }
        array[0]--;
        return temp;
    }

    // Deleting at the end O(1)
    int pop_back() {
        int n = currentSize();
        int temp = array[n];
        array[0]--;
        return temp;
    }

    // Deleting at the kth position O(n-k) -> O(n)
    int pop(int k) {
        int n = currentSize();
        int temp = array[k];
        for(int i=k; i<n; i++) {
            array[i] = array[i+1];
        }
        array[0]--;
        return temp;
    }

    // Accessing an element at the kth position O(1)
    int& operator[] (int k) {
        return array[k];
    }

    
};

#endif