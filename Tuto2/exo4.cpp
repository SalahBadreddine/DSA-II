#include <iostream>
#include <stack>

using namespace std;

template <class T>
class Stack {
private:
    T* array;
    const int theSize;
    int top1;
    int top2;
public:
    Stack (int s) : theSize(s) {
        array = new T[theSize];
        top1 = -1;
        top2 = theSize;
    }

    ~Stack () {
        delete [] array;
    }

    void pushInStack1 (const T& element) {
        if (top1 < top2-1) {
            array[++top1] = element;
        } else {
            throw std::out_of_range("You reached the maximum size");
        }
    }

    void pushInStack2 (const T& element) {
        if (top2 > top1+1) {
            array[++top2] = element;
        } else {
            throw std::out_of_range("You reached the maximum size")
        }
    }

    bool isEmpty() {
        return ((top1 == -1) && (top2 == theSize));
    }

    void popFromStack1 () {
        if (top1 == -1) {
            throw std::exception("The stack 1 is empty")
        } 
        top1--;
    }

    void popFromStack2 () {
        if (top2 == -1) {
            throw std::exception("The stack 1 is empty")
        } 
        top2--;
    }
};