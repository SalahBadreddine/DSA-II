#include <iostream>

using namespace std;

bool func (int A[], int n) {
    if (n==0) {
        return false;
    }
    if (A[n/2] == n/2) {
        return true;
    }
    if(A[n/2] < n/2) {
        return func(A, n/2);
    } 
    return func(A, 3*n/2);
}

int main () 
{
    int A[5] = {0, 1, 2, 3, 4};
    cout << func(A, 5 ) << endl;
    return 0;
}

// The runnong time of the algorithm is O(N) in worst case, where N is the size of the array