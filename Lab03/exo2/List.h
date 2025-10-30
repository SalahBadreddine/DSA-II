#include <iostream>
using namespace std;

template <class Obj>
class List {
public:
    struct Node {
        Obj data;
        Node * next;
        Node (const Obj& data, Node* next=nullptr) {
            this->data = data;
            this->next = next;
        }
    };

    Node* head;

    List() : head(nullptr), listSize(0) {}
    ~List() {
        Node* current = this->head;
        while (current != nullptr) {
            Node* temp = current->next;
            current = current->next;
            delete temp;
        }
    }

    int size() { // Running time is O(N)
        if (head == nullptr) {
            return 0;
        }
        int s = 0;
        Node* current = head;
        while (current != nullptr) {
            current = current->next;
            s++;
        }
        return s;
    }

    void printList() { // Running time is O(N)
        Node* current = this->head;
        while (current != nullptr) {
            cout << current->data << " ";
            current = current->next;
        }
        cout << endl;
    }

    bool testValue (const Obj& x) { // Running time is O(N)
        Node* current = this->head;
        while (current != nullptr) {
            if (current->data == x) {
                return true;
                break;
            }
            current = current->next;
        }
        return false;
    }

    void push_front(const Obj& x) { // Running time is O(N)
        if (!testValue(x)) {
            Node* newNode = new Node(x, head);
            head = newNode;
        }
    }

    void push_back (const Obj& x) { // Running time is O(N)
        if(!testValue(x)) {
            Node* current = head;
            while (current->next != nullptr) {
                current = current->next;
            }
            Node* newNode = new Node(x, nullptr);
            current->next = newNode;
        }
    }

    void removeX (const Obj& x) { // Running time is O(N)
        if(!testValue(x)) 
            return;
        if (head->data == x) {
            Node* temp = head;
            head = head->next;
            delete temp;
            return;
        }
        Node* current = head;
        while (current->next->data != x) {
            current = current->next;
        }
        Node* temp = current->next;
        current->next = temp->next;
        delete temp;
    }

    // Exo3 
    void swapAdjacent(int pos) {
        if (size() < 2) return;

        Node* current = head;
        for (int i = 1; current != nullptr && i < pos - 1; i++) {
            current = current->next;
        }

        Node* first = current->next;
        Node* second = first->next;
        first->next = second->next;
        second->next = first;
        current->next = second;
    }

    // Exo4
    List intersection (const List& other) { // Running time is: O(N), and it is preferably to take N = min(size1, size2)
        List res ;
        Node* current1 = this->head;
        Node* current2 = other->head;
        while (current1 != nullptr && current2 != nullptr) {
            while (current1->data < current2->data) {
                current1 = current1->next;
            }
            while (current1->data > current2->data) {
                current2 = current2->next;
            }
            if (current1->data == current2->data) {
                res.push_back(current1->data);
            }
        }
        return res;
    }

};  

