#include <iostream>
#include <cstdlib>
#include <list>
#include <chrono>

using namespace std;

void printLots (list<int> L, list<int> P) {
    auto it = L.begin();
    int index = 1;
    for (int pos: P) {
        while (index < pos && it != L.end()) {
            index++;
            it++;
        }
        if (it != L.end() && index == pos) {
            std::cout << *it << " ";
        }
    }
    cout << endl;
}

// The complexity of the algorithm is: O(n), where n is the size of the list P

int main()
{
    list<int> L = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    list<int> P = {3, 6, 8};
    auto start = chrono::high_resolution_clock::now();
    for (int i=0; i<10; i++) {
        printLots(L, P);
    }
    auto end = chrono::high_resolution_clock::now();
    chrono::duration<double> duration = end - start ;
    cout << "The running time of the algorithm is: " << duration.count() << "s" << endl;
    return 0;
}

// cd "/Users/macbook/Desktop/DSA 2/Lab03/" && g++ -std=c++11 exo1.cpp -o exo1 && "/Users/macbook/Desktop/DSA 2/Lab03/exo1"

