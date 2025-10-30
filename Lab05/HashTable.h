#ifndef HASHTABLE_H
#define HASHTABLE_H

#include <cmath>

class HashTable {
private:
    int TABLESIZE;
    int* array;
    int collisions;
     
    int hash(int key) {
        return ((key%TABLESIZE) + TABLESIZE) % TABLESIZE;
    }

public:
    HashTable (int size): TABLESIZE(size) {
        array = new int [TABLESIZE];
        for (int i=0; i<TABLESIZE; i++) {
            array[i] = -1; // convention -1 for empty cells 
        }
        collisions = 0;
    }

    ~HashTable() {
        delete [] array;
    }

    void insert (int key) {
        int index = hash(key);
        if (array[index] != -1) {
            collisions++;
        } 
        array[index] = key;
    }

    int operator [] (int key) {
        return array[hash(key)];
    }

    void remove (int key) {
        array[hash(key)] = -1;
    }

    int getCollisions() const {
        return collisions;
    }

};



#endif