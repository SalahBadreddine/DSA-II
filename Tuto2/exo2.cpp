#include <iostream>
using namespace std;

template<class T>
class LinkedList {
    struct Node {
        T data;
        Node* next;
        Node(const T& data = T(), Node* next=nullptr) : data(data), next(next) {};
    };

private:
    Node* head;
    Node* tail; // optional but would help accessing last element

public:
    LinkedList () {
        head = nullptr;
        tail = nullptr;
    }

    ~LinkedList() {
        Node* current = head;
        while (current != nullptr) {
            Node* nextNode = current->next;
            delete current;
            current = nextNode;
        }
        head = nullptr;
    }

    // Add an element at the beginning O(1)
    void push_front(const T& element) {
        Node* temp = head;
        Node* newNode = new Node(element, head);
        head = newNode;
        if (temp == nullptr) { // means that the list was empty
            tail = head;
        }
    }

    // Add an element at the end O(1)
    void push_back(const T& element) {
        Node* newNode = new Node(element, nullptr);
        if (head == nullptr) {
            head = newNode;
            tail = newNode;
            return ;
        } 
        tail->next = newNode;
        tail = newNode;
    }

    // Adding at the kth position O(k) -> O(n)
    void push(const T& element, int k) {
        if (k<1) return;
        Node* current = head;
        for(int i=1; (i<k && current); i++) {
            current = current->next ;
        }
        if (current) {
            Node* newNode = new Node(element, current->next);
            current->next = newNode;
        }
    }

    // Finding an element 
    bool Find(const T& data) {
        Node* current = head;
        while (current) {
            if(current->data == data) {
                return true;
            }
            current = current->next;
        }
        return false;
    }

    // Deleting at the kth position O(k)
    void pop(int k) {
        if (k < 1) {
            return ;
        }
        if(k == 1) {
            pop
        }
        int count;
        Node* current = head;
        for (count=1; (count<k) && current; count++) {
            current = current->next; // Move to the k-1th node
        }
        if(count == k && current->next) {
            Node* temp = current->next;
            current->next = temp->next;
            delete temp;
        }
    }

    // Deleting at the beginning O(1)
    void pop_front() {
        if (head == tail) {
            delete head;
            head = nullptr;
            tail = nullptr;
            return;
        }
        Node* temp = head;
        head = head->next;
        delete temp;
    }

    //Deleting at the end O(n)
    void pop_back() {
        if (head == tail) {
            delete head;
            head = nullptr;
            tail = nullptr;
            return;
        }
        Node* current = head;
        while (current->next != tail) {
            current = current->next;
        }
        Node* temp = tail;
        current->next = nullptr;
        tail = current;
        delete temp;
    }

    T front() {
        return head->data;
    }

    T back() {
        return tail->data;
    }

    bool isEmpty () {
        return (head == nullptr);
    }

    void insertBefore (const T& element, Node* pos) {
        Node* newNode = new Node;
        newNode->data = pos->data;
        newNode->next = pos->next;
        pos->data = element;
        pos->next = newNode;
    }

    void removeAt (Node* pos) {
        Node* temp = pos->next;
        pos->data = temp->data;
        pos->next = temp->next;
        delete temp;
    }
};