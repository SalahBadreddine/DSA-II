#ifndef CIRCULAR_QUEUE_H
#define CIRCULAR_QUEUE_H

#include <stdexcept>

template<class T>
class CircularQueue {
private:
    const int maximum;
    T* array;
    int front;
    int back;

public:
    CircularQueue(int max): maximum(max) {
        array = new T [maximum];
        front = -1;
        back = -1;
    }

    ~CircularQueue() {
        delete [] array ;
    }

    void enqueue(const T& element) {
        if (isEmpty()) {
            throw out_of_range("The Queue is full !");
        } else {
            size++;
            array[back] = element;
            back = (back+1)%maximum;
        }
    }

    T dequeue() {
        if (size == 0) {
            return out_of_range("The Queue is empty !");
        } else {
            size--;
            T res = array[front];
            front = (front+1)%maximum;
            return res;
        }
    }

    bool isEmpty() {
        return (front )
    }

    bool full () {
        
    }
};

#endif