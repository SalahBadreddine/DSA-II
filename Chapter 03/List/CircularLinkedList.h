#ifndef CIRCULAR_H
#define CIRCULAR_H


template<class T>
class CircularLinkedList {
    struct Node {
        T data;
        Node* next;
        Node (const T& data=T(), Node* next=nullptr): data(data), next(next) {}
    };

private:
    Node* head;
    Node* tail;

public:
    CircularLinkedList() {
        head = nullptr;
    }

    ~CircularLinkedList() {
        Node* current = head;
        while (current) {
            Node* temp = current->next;
            delete current;
            current = temp;
        }
    }

    push_front(const T& element) {
        if (!head) {
            Node* newNode = new Node(element, newNode);
            head = newNode;
            tail = newNode;
            return ;
        }
        Node* newNode = new Node (element, head);
        head = newNode;
        tail->next = head;
    }

    // This line is the most important "tail->next = head;"
};

#endif