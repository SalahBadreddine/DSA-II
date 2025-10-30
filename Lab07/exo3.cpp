//
// Figure 7.15 Driver for quicksort
// Quicksort algorithm (driver).

#include <iostream>
#include <algorithm>
#include <vector>
#include "Sort.h"

using namespace std;

template <typename Comparable>
void quicksort( vector<Comparable> & a )
{
	quicksort( a, 0, a.size( ) - 1 );
}

//
/* Figure 7.16 Code to perform median-of-three partitioning
* Return median of left, center, and right.
* Order these and hide the pivot.
*/
template <typename Comparable>
const Comparable & median3( vector<Comparable> & a, int left, int right )
{
	int center = ( left + right ) / 2; // we calculate the center of the current array 

    // These 3 conditions are performed to find the median which will be stored in a[center]
	if( a[ center ] < a[ left ] )
		std::swap( a[ left ], a[ center ] );
	if( a[ right ] < a[ left ] )
		std::swap( a[ left ], a[ right ] );
	if( a[ right ] < a[ center ] )
		std::swap( a[ center ], a[ right ] );

	// Place pivot at position right - 1  (I HAVE CHANGED THIS TO "Place pivot at position right"
	std::swap( a[ center ], a[ right ] );  // INSTEAD OF std::swap( a[ center ], a[ right - 1 ] ); 
	return a[ right ];  // INSTEAD OF return a[ right - 1 ];
}

//
// Figure 7.17 Main quicksort routine
//
/**
* Internal quicksort method that makes recursive calls.
* Uses median-of-three partitioning and a cutoff of 10.
* a is an array of Comparable items.
* left is the left-most index of the subarray.
* right is the right-most index of the subarray.
*/
template <typename Comparable>
void quicksort( vector<Comparable> & a, int left, int right )
{
	if( left + 10 <= right ) // otherwise, we perform insertion sort directly 
    // Why ? we often avoid consuming the momeory and cpu on small sub arrays and tend to use insertion sort 
    // for more efficiency 
	{
		const Comparable & pivot = median3( a, left, right ); // we retrieve the pivot using median 3 method 
        // + it places the pivot in the right 

		// Begin partitioning
		int i = left, j = right - 1;
		for( ; ; )
		{
			while( a[ ++i ] < pivot ) { } // This loop try to find a bigger element than the pivot to be swapped in the right
			while( pivot < a[ --j ] ) { } // This loop try to find a smaller element than the pivot to be swapped in the left side 
			if( i < j ) // Make sure we didn't cross + finds the position of the pivot (i)
				std::swap( a[ i ], a[ j ] );
			else
				break;
		}
		
		// Restore pivot
		std::swap( a[ i ], a[ right ] );     // INSTEAD OF std::swap( a[ i ], a[ right - 1 ] );


		quicksort( a, left, i - 1 );  // Sort small elements
		quicksort( a, i + 1, right ); // Sort large elements
	}

	else // Do an insertion sort on the subarray
		insertionSort( a, left, right );
}

// The running time of quick sort for sorted, reverse-ordered and random input:
// It depends on the choice of the pivot but for a good method like median of 3, we have 
// Random input -> O(n*log(n)), from Master theorem since T(n) = 2 * T(n/2) + n in average 
// Sorted input -> O(n*log(n))
// Reverse ordered input -> O(n*log(n))