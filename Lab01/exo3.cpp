#include <iostream>
#include <stdexcept>

using namespace std ;

template <class T>

class Collection {
private:
    T* data;
    const int capacity;
    int currentSize;

public:
    Collection(const int & size) : capacity(size) {
        this->data = new T[capacity];
        currentSize = 0;
    }

    ~Collection () {
        delete [] data ;
    }

    bool isEmpty() {
        return (this->currentSize == 0);
    }

    void makeEmpty() {
        this->currentSize = 0;
    }

    void insert(const T& element) {
        if (currentSize == capacity) {
            throw(out_of_range("The collection is full"));
        }
        data[currentSize++] = element ;
    }

    void remove(const T& element) {
        if(isEmpty()) {
            throw(out_of_range("The collection is empty"));
        }
        for (int i=0; i<currentSize; i++) {
            if(data[i] == element) {
                for(int j=i; j<currentSize; j++) {
                    data[j] = data[j+1]
                }
                currentSize--;
                break;
            }
        }
    }

    bool contains(const T& element) {
        for (int i=0; i<currentSize; i++) {
            if (data[i] == element) {
                return true ;
            }
        }
        return false ;
    }

};