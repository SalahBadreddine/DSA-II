#include <iostream>
#include "../Chapter 03/Stack/Stack.h"

using namespace std;

template <class T>
class VStack {
private:
    Stack<T> keepMin;
    Stack<T> stack;

public:
    VStack() {} // Default constructor
    
    void push(const T& element) {
        stack.push(element);
        if (element <= keepMin.front()) {
            keepMin.push(element);
        }
    }

    T pop () {
        T res = stack.pop();
        if (res == keepMin.fron()) {
            keepMin.pop();
        }
        return res;
    }

    T findMin() {
        return keepMin.front();
    }
};