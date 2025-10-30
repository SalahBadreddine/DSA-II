#include <iostream>
#include <vector>
#include <cmath>
#include <cstdlib>

using namespace std;

class CuckooHashTable {
private:
    vector<int> table;
    int size;
    int maxIterations; // to check the case of infinite loop 

    int hash1(int key) {
        return key % size/2; // from top
    }

    int hash2(int key) {
        return size/2 + hash1(key); // from bottom 
    }

    void rehash() {
        cout << "Rehashing...\n";
        vector<int> oldTable = table;
        size *= 2;  //Double the size
        table.assign(size, -1);  //Initialize with -1 for (empty)
        
        for (int key : oldTable) {
            if (key != -1) {
                insert(key);  //Reinsert all keys
            }
        }
    }

public:
    CuckooHashTable(int initSize) : size(initSize), maxIterations(10) {
        table.assign(size, -1);  //Initialize with -1 (empty)
    }

    void insert(int key) {
        int position, temp, iteration = 0;
        while (iteration < maxIterations) {
            position = (iteration % 2 == 0) ? hash1(key) : hash2(key);

            if (table[position] == -1) {
                table[position] = key;
                return;
            }

            temp = table[position];
            table[position] = key;
            key = temp;
            iteration++;
        }
        rehash();
        insert(key); 
    }

    bool search(int key) {
        return table[hash1(key)] == key || table[hash2(key)] == key;
    }

    void printTable() {
        for (int i = 0; i < size; ++i) {
            cout << i << ": " << (table[i] == -1 ? "Empty" : to_string(table[i])) << endl;
        }
    }
};

int main() {
    CuckooHashTable table(7);

    table.insert(10);
    table.insert(20);
    table.insert(15);
    table.insert(15);
    table.insert(35);

    cout << "Hash Table:\n";
    table.printTable();

    cout << "Search for 15: " << (table.search(15) ? "Found" : "Not Found") << endl;
    return 0;
}
