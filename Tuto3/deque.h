#ifndef DEQUE_H
#define DEQUE_H

#include <iostream>
#include <list>

using namespace std;

template <class T>
class dequeue {
private:
    list<T> l;

public:
    // Default constructor
    
    void push (const T& x) {
        l.push_front(x);
    }

    void inject(const T& x) {
        l.push_back(x);
    }
    
    T pop() {
        if (l.empty()) {
            throw std::out_of_range("The deque is empty !")
        }
        T item = l.front();
        l.pop_front();
        return item;
    }

    T eject () {
        if (l.empty()) {
            throw std::out_of_range("The deque is empty !")
        }
        T item = l.back();
        l.pop_back();
        return item;
    }
};

#endif