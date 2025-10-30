#ifndef QUEUE_H
#define QUEUE_H

#include "../List/LinkedList.h"

template <class T>
class Queue {
private:
    LinkedList<T> list;

public:
    Queue () {}

    // Add an element from the end O(1)
    void enqueue(const T& element) {
        list.push_back(element);
    }

    // Remove an element from the beginning
    T dequeue () {
        T front = list.front();
        list.pop_front();
        return front;
    }

};

#endif