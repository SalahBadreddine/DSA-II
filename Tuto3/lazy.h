#ifndef LAZY_H
#define LAZY_H

#include <iostream>
using namespace std;

template <class T>
class lazy {
    struct Node {
        T data;
        Node* next;
        bool isDeleted;

        Node (const T& data=T(), Node* next = nullptr, bool isDeleted=false) : data(data), next(next), isDeleted(isDeleted) {}
    };

private:
    Node* head;
    int size;
    int deletedCount;

public:
    lazy() : head(nullptr), size(0), deletedCount(0) {}

    ~lazy() {
        Node* current = head;
        while (current) {
            Node* temp = current->next;
            delete current;
            current = current->next;
        }
    }

    bool isEmpty () {
        return (size == 0);
    }

    // Inserting at the beginning
    void insert(const T& x) {
        Node* newNode = new Node(x, head);
        head = newNode;
        size++;
    }

    // Search for a value in the linked list
    bool search (const T& x) {
        Node* current = head;
        while (current) {
            if (!(current->isDeleted) && current->data == x) {
                return true;
            }
            current = current->next;
        }
        return false;
    }

    // Mark a node with a specific value as deleted 
    void deleteElement (const T& x) {
        if (!search(x)) {
            throw exception("The data doesn't exist")
        }
        Node* current = head;
        while (current) {
            if (!(current->isDeleted) && current->data == x) { // Element to be deleted
                current->isDeleted = true;
                deletedCount++;
                if (deletedCount >= size/2) {
                    cleanup();
                }
                return;
            }
            current = current->next;
        }
    }

    void cleanup () {
        Node* current = head;
        Node* previous = head;
        while (current) {
            if (current->isDeleted) {
                if (current != head) {
                    previous->next = current->next;
                    delete current;
                    current = previous->next;
                    continue;
                } else {
                    head = head->next;
                    delete current;
                    current = head;
                    previous = head;
                }
            }
            previous = current;
            current = current->next;
        }
    }
};

#endif