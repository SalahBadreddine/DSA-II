#include <iostream>
#include <stdexcept>
using namespace std;

int findCondidate(int *A, int n) {
    // Base case 
    if (n == 0) {
        throw out_of_range("There is no majority element");
    }
    if (n == 1) {
        return A[0];
    }

    int* B = new int[n / 2 + 1]; 
    int m = 0;
    for (int i = 0; i < n - 1; i += 2) {
        if (A[i] == A[i + 1]) {
            B[m] = A[i];
            m++;
        }
    }
    // If n is odd, we just add the last element
    if (n % 2 == 1) {
        B[m] = A[n - 1];
        m++;
    }

    int candidate = findCondidate(B, m);
    delete[] B; 
    return candidate;
}

int findMajorityElement(int *A, int n) {
    int candidate = findCondidate(A, n);
    int count = 0;

    for (int i = 0; i < n; i++) {
        if (A[i] == candidate) {
            count++;
        }
    }

    if (count > n / 2) {
        return candidate;
    } else {
        throw out_of_range("There is no majority element");
    }
}

int main() {
    int A[10] = {1, 2, 1, 2, 1, 2, 1, 2, 1, 2};
    int B[11] = {1, 2, 1, 2, 1, 2, 1, 2, 1, 2, 1};
    
    try {
        cout << "The majority element of the array A is: " << findMajorityElement(A, 10) << endl;
    } catch (const exception& e) {
        cout << e.what() << endl;
    }

    try {
        cout << "The majority element of the array B is: " << findMajorityElement(B, 11) << endl; // Use size 11 for B
    } catch (const exception& e) {
        cout << e.what() << endl;
    }

    return 0;
}