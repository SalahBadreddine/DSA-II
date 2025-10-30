#include <iostream>
#include <stdexcept>

using namespace std ;

template <class T>

class OrderedCollection {
private:
    T* data ;
    int capacity ;
    int currentSize ;
public:
    OrderedCollection(const int & size): capacity(size) {
        data = new T[capacity] ;
        currentSize = 0 ;
    }

    ~OrderedCollection() {
        delete [] data ;
    }

    bool isEmpty() {
        return (currentSize == 0) ;
    }

    void makeEmpty() {
        currentSize = 0 ;
    }

    void insert (const T& element) {
        if (currentSize == capacity) {
            T* temp = new T[capacity] ;
            temp = data ;
            delete [] data ;
            capacity *= 2;
            data = new T[capacity];
            for (int i=0; i<currentSize; i++) {
                data[i] = temp[i];
            }
            delete [] temp;
        }
        currentSize++;
        int i=0;
        while(data[i+1] < element && i<currentSize) {
            i++;
        }
        for(int j=i+1; j<currentSize; j++) {
            data[j] = data[j-1];
        }
        data[i] = element ;   
    }

    void remove(const T& element) {
        if (!isEmpty()) {
            for (int i=0; i<currentSize; i++) {
                if (data[i] == element) {
                    for (int j=i; j<currentSize-1; j++) {
                        data[j] = data[j+1] ;
                    }
                    currentSize -- ;
                }
            }
        }
    }

    T& findMin () {
        if (!isEmpty()) {
            return data[0] ;
        } else {
            throw(out_of_range("Collection is empty"));
        }
    }

    T& findMax () {
        if (!isEmpty()) {
            return data[currentSize] ;
        } else {
            throw(out_of_range("Collection is empty"));
        }
    }

};

int main() 
{
    OrderedCollection <double> collection1 (10) ;
    collection1.insert(1.8);
    collection1.insert(3.5);
    collection1.insert(0.77);
    collection1.insert(7.9);
    collection1.insert(8.0);
    collection1.remove(0.77);
    try {
        cout << "Before removing elements, the minimum value is: " << collection1.findMin() << endl;
        cout << "Before removing elements, the maximum value is: " << collection1.findMax() << endl;
        collection1.makeEmpty();
        cout << "Trying to find the min/max after removing items: " << endl;
        cout << collection1.findMin() << endl;
    }
    catch (exception& exception) {
        cout << exception.what() << endl;
    }
    return 0;
}