/**
 * Standard heapsort.
 */

#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;

/**
 * Internal method for heapsort that is used in
 * deleteMax and buildHeap.
 * i is the position from which to percolate down.
 * n is the logical size of the binary heap.
 */
/**
 * Internal method for heapsort.
 * i is the index of an item in the heap.
 * Returns the index of the left child.
 */

inline int leftChild( int i )
{
    return 2 * i + 1;
}

template <typename Comparable>
void percDown( vector<Comparable> & a, int i, int n ) // MAX HEAP 
{
    int child;
    Comparable tmp;

    for( tmp = std::move( a[ i ] ); leftChild( i ) < n; i = child )
    {
        child = leftChild( i );
        if( child != n - 1 && a[ child ] < a[ child + 1 ] ) // to get the greater child (ie if right child is smaller, we swap)
            ++child;
        if( tmp < a[ child ] ) // we perform perculate down, by swaping the parent element with its greater child 
            a[ i ] = std::move( a[ child ] );
        else
            break;
    }
    a[ i ] = std::move( tmp );
}


template <typename Comparable>
void heapsort( vector<Comparable> & a )
{
    for( int i = a.size( ) / 2 - 1; i >= 0; --i )  /* buildHeap */
        percDown( a, i, a.size( ) );
    for( int j = a.size( ) - 1; j > 0; --j )
    {
        std::swap( a[ 0 ], a[ j ] );               /* deleteMax */
        percDown( a, 0, j );
        // This will sort the elements in an ascending order 
        // since we used max heap 
    }
}

template <typename Comparable>
void heapsortInRange(vector<Comparable> &a, Comparable Low, Comparable High) {
    // Filter elements in range
    vector<Comparable> filtered;
    for (const auto &val : a) {
        if (val >= Low && val <= High)
            filtered.push_back(val);
    }

    // Sort the filtered array
    heapsort(filtered);

    // Replace the original array with sorted filtered elements
    a = move(filtered);
}

int main() {
    vector<int> data;
    int a[] = {142, 543, 123, 65, 453, 879, 572, 434, 111, 242, 811, 102};
    for (int i=0; i<12; i++) {
        data.push_back(a[i]);
    }
    cout << "Original Data: ";
    for (const auto &val : data)
        cout << val << " ";
    cout << endl;

    heapsort(data);

    cout << "Sorted Data: ";
    for (const auto &val : data)
        cout << val << " ";
    cout << endl;

     cout << "Original Data: ";
    for (const auto &val : data)
        cout << val << " ";
    cout << endl;

    heapsortInRange<int>(data, 100, 600);

    cout << "Sorted Data in range 100 to 600: ";
    for (const auto &val : data)
        cout << val << " ";
    cout << endl;

    return 0;
}

// g++ -std=c++11 exo4.cpp -o exo4 && ./exo4