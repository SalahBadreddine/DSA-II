#ifndef DOUBLY_LINKED_LIST_H
#define DOUBLE_LINKED_LIST_H


template<class T>
class DoublyLinkedList {
    struct Node {
        T data;
        Node* prev;
        Node* next;
        Node(const T& data = T(), Node* prev=nullptr, Node* next=nullptr): data(data), prev(prev), next(next) {};
    };

private:
    Node* head;
    Node* tail;

public:
    DoublyLinkedList() {
        head = nullptr;
        tail = nullptr;
    }

    ~DoublyLinkedList() {
        Node* current = head;
        while (current) {
            Node* temp = current->next;
            delete current;
            current = current->next;
        }
    }

    // Add an element at the beginning O(1)
    void push_front(const T& element) {
        Node* newNode = new Node(element, nullptr, head);
        if (head) {
            head->prev = newNode;
        } else {
            tail = newNode;
        }
        head = newNode;
    }

    // Add an element at the end O(1)
    void push_back(const T& element) {
        Node* newNode = new Node(element, tail, nullptr);
        if (tail) {
            tail->next = newNode;
        } else {
            head = newNode;
        }
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
            Node* newNode = new Node(element, current, current->next);
            if(current->next) {
                current->next->prev = newNode;
            } else {
                tail = newNode;
            }
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

    // Deleting at the beginning O(1)
    void pop_front() {
        if (head == tail) {
            delete head;
            head = nullptr;
            tail = nullptr;
            return ;
        } 
        Node* temp = head;
        head = head->next;
        head->prev = nullptr;
        delete temp;
    }

    //Deleting at the end O(1)
    void pop_back() {
        if (head==tail) {
            pop_front();
            return;
        }
        Node* temp = tail;
        tail = tail->prev;
        tail->next = nullptr;
        delete temp;
    }

    // Reversing is easy O(n)
    void reverse() {
        Node* current = head;
        while (current) {
            Node* temp = current->prev;
            current->prev = current->next;
            current->next = temp;
            current = current->prev;
        }
        if(tail) {
            Node* temp = head;
            head = tail;
            tail = temp;
        }
    }
}; 


#endif