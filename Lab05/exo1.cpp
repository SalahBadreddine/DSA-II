#include <iostream>
#include "HashTable.h"
#include <ctime>

using namespace std;

void performExperiment(int fillPercentage) {
    const int TABLESIZE = 1000;
    HashTable ht(TABLESIZE);
    int numInsertions = (TABLESIZE * fillPercentage) / 100;
    
    srand(static_cast<unsigned>(time(nullptr))); // Seed for random values

    for (int i = 0; i < numInsertions; ++i) {
        int value = rand();
        ht.insert(value);
    }

    cout << "Fill Percentage: " << fillPercentage << "%, Collisions: " << ht.getCollisions() << endl;
}

int main() {
    performExperiment(20); // 20% fill
    performExperiment(50); // 50% fill
    performExperiment(80); // 80% fill

    return 0;
}