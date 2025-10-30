#ifndef STACK_H
#define STACK_H

#include <iostream>
#include "../List/LinkedList.h"
#include "stdexcept"

template <class T>
class Stack {
private:
    LinkedList<T> list;
public:
    void push(const T& element) {
        list.push_front(element);

    }

    T pop() {
        if (!isEmpty()) {
            T res = list.front();
            list.pop_front();
            return res;
        } 
        throw out_of_range("The stack is empty");
    }

    bool isEmpty() const {
        return list.isEmpty();
    }

    T front () const {
        return list.front();
    }

    T back () const {
        return list.back();
    }
};

#endif