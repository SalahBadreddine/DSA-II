#include <iostream>
#include <vector>
#include "Sort.h"

using namespace std;

int main () 
{
    vector<int> v;
    int arr[] = {3, 1, 4, 1, 5, 9, 2, 6, 5};
    for (int i=0; i<9; i++) {
        v.push_back(arr[i]);
    }
    for (int i=0; i<v.size(); i++) {
        cout << v[i] << ", ";
    }
    cout << endl;
    insertionSort<int>(v);
    for (int i=0; i<v.size(); i++) {
        cout << v[i] << ", ";
    }
    cout << endl;
}

// The running time when all elements are equal is O(n) because it only performs n comparaisons, 
// and never swaps elements (ie inversions = 0) so the first loop iterates n times and inner loop has constant time 
// O(1)