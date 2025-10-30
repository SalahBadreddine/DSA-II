#include <iostream>
#include <cstdlib>
#include <chrono>

using namespace std;

double kthLargestElement(double * arr, int size, int k) {
    for (int i=0; i<size-1; i++) { // Bubble sort
        for (int j=i; j<size; j++) {
            if(arr[j] < arr[i]) {
                swap(arr[i], arr[j]) ;
            }
        }
    }

    return arr[k-1] ;
}

int main()
{
    double arr[10] = {1, 5, 2, 10, 6, 0, 7, 9, 8, 3} ;
    cout << "The 2nd largest element is: " << kthLargestElement(arr, 10, 2) << endl;
    int N_values[8] = {10, 100, 1000, 10000, 20000, 50000, 100000, 500000};
    for (int i=0; i<8; i++) {
        double * arr = new double[N_values[i]];
        for (int i=0; i<N_values[i]; i++) {
            arr[i] = rand()%10000 + 1;
        }
        int k = N_values[i]/2;
        auto start = chrono::high_resolution_clock::now();
        int kthLargest = kthLargestElement(arr, N_values[i], k);
        auto end = chrono::high_resolution_clock::now();
        chrono::duration<double> running_time = end - start;

        cout << "Value: " << k << ", Duration: " << running_time.count() << endl;
    }
}