#include <iostream>
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
    mergeSort<int>(v);
    for (int i=0; i<v.size(); i++) {
        cout << v[i] << ", ";
    }
    cout << endl;
}

// The running time of merge sort for sorted array is: n/2 * log(n) -> O(n*log(n))
// The running time of merge sort for reversed-ordered array is: O(n*log(n))
// The running time of merge sort for random array is: O(n*log(n)) 
// it remains consistent, and the general formula is T(n) = 2 T(n/2) + n 

// Using iterative way 
template <typename Comparable>
void mergeSortIterative( vector<Comparable> & a, vector<Comparable> & tmpArray)
{   
   int n = a.size();
    
    // first loop, it iterates the size, from 2 to n (number of iterations is logN) to fix the size of sub arrays
    for (int size = 1; size < n; size *= 2) {
        // we get the sub arrays and we merge them 
        for (int start = 0; start < n; start += 2 * size) {
            int mid = std::min(start + size, n);
            int end = std::min(start + 2 * size, n);
            merge(a, tmpArray, start, mid, end);
        }

        // or 
        int part1Start = 0;
        while (part1Start + size * 2 < n-1) {
            int part2Start = part1Start + size * 2;
            int part2End = min(n, part2Start + size * 2 -1);
            merge(a, tmpArray, part1Start, part2Start, part2End);
            part1Start = part2End + 1;
        }
    }

    
}


