#ifndef TEAM_QUEUE_H
#define TEAM_QUEUE_H

#include <stdexcept>

template <class T>
class TeamQueue {
private:
    struct Node {
        T element;
        T team;
        Node* next;

        Node(const T& element = T(), const T& team = T(), Node* next = nullptr) {};
    };

    Node* head;
    Node* tail;

public:
    TeamQueue () : head(nullptr), tail(nullptr) {};
    
    ~TeamQueue() {
        Node* current = head;
        while (current) {
            Node* temp = current->next;
            delete current;
            current = current->next;
        }
        head = nullptr;
    }

    void Enqueue(const T& element, const T& team) { // O(n) 
        Node* current = head;
        while (current && current->team != team) {
            current = current->next;
        }
        if (current == nullptr) {
            // new team, we insert it at the beginning
            Node* newNode = new Node(element, team, nullptr);
            tail->next = newNode;
            tail = newNode;
        } else {
            // We found the team
            while (current->next && current->next->team == team){
                current = current->next;
            }
            Node* newNode = new Node(element, team, current->next);
            current->next = newNode;
            if (current == tail) {
                tail = newNode;
            }
        }
    }

    T Dequeue () { // O(1)
        if (head == nullptr) {
            throw exception ("The queue is empty")
        } else {
            T element = head->element;
            Node* temp = head;
            head = head->next;
            delete temp;
            return element;
        }
    }

    bool SearchElement (const T& element) { // O(n)
        Node* current = head;
        while (current) {
            if (current->element == element) {
                return true;
            }
            current = current->next;
        }
        return false;
    }

    bool SearchTeam (const T& team) {
        Node* current = head;
        while (current) {
            if (current->team == team) {
                return true;
            }
            current = current->next;
        }
        return false;
    }
};

#endif