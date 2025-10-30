#include <iostream>
#include <vector>

using namespace std;

class HopscotchHashTable {
private:
    struct Bucket {
        int key;
        bool occupied;
        vector<bool> hopInfo;

        Bucket() : key(-1), occupied(false), hopInfo(4, false) {}
    };

    vector<Bucket> table;
    int size;
    const int maxDistance = 4; 

    int hash(int key) {
        return key % size;
    }

    void rehash() {
        cout << "Rehashing...\n";
        vector<int> keys;

        for (Bucket bucket : table) {
            if (bucket.occupied) keys.push_back(bucket.key);
        }

        size *= 2;
        table.assign(size, Bucket());

        for (int key : keys) {
            insert(key);
        }
    }

public:
    HopscotchHashTable(int initSize) : size(initSize) {
        table.assign(size, Bucket());
    }

    void insert(int key) {
        int pos = hash(key);

        // Check if we can insert directly in the neighborhood
        for (int i = 0; i < maxDistance; ++i) {
            int currentPos = (pos + i) % size;

            if (!table[currentPos].occupied) {
                table[currentPos].key = key;
                table[currentPos].occupied = true;
                table[pos].hopInfo[i] = true; // Mark it in the hopInfo
                return;
            }
        }

        // If neighborhood is full, search for an available slot
        int freePos = (pos + maxDistance) % size;
        while (table[freePos].occupied) {
            freePos = (freePos + 1) % size;

            // and we Rehash if no space found
            if (freePos == pos) {
                rehash();
                insert(key);
                return;
            }
        }

        // Move items to make room for the new key within the neighborhood
        while ((freePos - pos)%size >= maxDistance) {
            bool moved = false;

            for (int i = freePos - maxDistance; i < freePos; ++i) {
                int bucketPos = i % size;

                for (int j = 0; j < maxDistance; ++j) {
                    if (table[bucketPos].hopInfo[j]) {
                        int neighborPos = (bucketPos + j) % size;

                        table[freePos] = table[neighborPos];
                        table[neighborPos].occupied = false;
                        table[bucketPos].hopInfo[j] = false;
                        table[bucketPos].hopInfo[freePos - bucketPos] = true;

                        freePos = neighborPos;
                        moved = true;
                        break;
                    }
                }

                if (moved) break;
            }

            if (!moved) {
                rehash();
                insert(key);
                return;
            }
        }

        // Insert the key in the freed slot
        table[freePos].key = key;
        table[freePos].occupied = true;
        table[pos].hopInfo[freePos - pos] = true;
    }

    bool search(int key) {
        int pos = hash(key);

        for (int i = 0; i < maxDistance; ++i) {
            int currentPos = (pos + i) % size;

            if (table[pos].hopInfo[i] && table[currentPos].key == key) {
                return true;
            }
        }
        return false;
    }

    void printTable() {
        for (int i = 0; i < size; ++i) {
            cout << i << ": ";
            if (table[i].occupied) {
                cout << table[i].key << " [";
                for (bool hop : table[i].hopInfo) cout << hop;
                cout << "]";
            } else {
                cout << "Empty";
            }
            cout << endl;
        }
    }
};

int main() {
    HopscotchHashTable table(7);

    table.insert(10);
    table.insert(20);
    table.insert(15);
    table.insert(35);
    table.insert(25);
    table.insert(50);

    cout << "Hash Table:\n";
    table.printTable();

    cout << "\nSearch for 15: " << (table.search(15) ? "Found" : "Not Found") << endl;
    cout << "Search for 99: " << (table.search(99) ? "Found" : "Not Found") << endl;

    return 0;
}
