#ifndef SPCHAIN
#define SPCHAIN

#include <vector>
#include <functional>
#include "./Chapter 03/List/LinkedList.h" 

using namespace std;

int nextPrime(int n);

// SeparateChaining Hash table class
//
// ******************PUBLIC OPERATIONS*********************
// bool insert( x )       --> Insert x
// bool remove( x )       --> Remove x
// bool contains( x )     --> Return true if x is present
// void makeEmpty( )      --> Remove all items

template <typename HashedObj>
class HashTable {
public:
    explicit HashTable(int size = 101) : currentSize{0} {
        theLists.resize(101);
    }

    bool contains(const HashedObj& x) const {
        auto& whichList = theLists[myhash(x)];
        return whichList.find(x);
    }

    void makeEmpty() {
        for (auto& thisList : theLists) {
            while (!thisList.isEmpty()) {
                thisList.remove(thisList.front());
            }
        }
    }

    bool insert(const HashedObj& x) {
        auto& whichList = theLists[myhash(x)];
        if (whichList.Find(x)) {
            return false;
        }
        whichList.push_back(x);

        // Rehash if the load factor exceeds the threshold
        if (++currentSize > theLists.size()) {
            rehash();
        }

        return true;
    }

    bool insert(HashedObj&& x) {
        auto& whichList = theLists[myhash(x)];
        if (whichList.Find(x)) {
            return false;
        }
        whichList.push_back(std::move(x));

        // Rehash if the load factor exceeds the threshold
        if (++currentSize > theLists.size()) {
            rehash();
        }

        return true;
    }

    bool remove(const HashedObj& x) {
        auto& whichList = theLists[myhash(x)];
        if (whichList.Find(x)) {
            whichList.remove(x);
            return true;
        }
        return false;
    }

private:
    vector<LinkedList<HashedObj>> theLists; // The array of LinkedLists
    int currentSize;

    void rehash() {
        vector<LinkedList<HashedObj>> oldLists = theLists;

        // Create new table with double the size
        theLists.resize(nextPrime(2 * theLists.size()));
        for (auto& thisList : theLists) {
            thisList = LinkedList<HashedObj>();
        }

        // Copy all elements to the new table
        currentSize = 0;
        for (auto& thisList : oldLists) {
            while (!thisList.isEmpty()) {
                insert(thisList.front());
                thisList.remove(thisList.front());
            }
        }
    }

    size_t myhash(const HashedObj& x) const {
        static hash<HashedObj> hf;
        return hf(x) % theLists.size();
    }
};

#endif