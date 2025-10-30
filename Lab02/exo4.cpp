#include <iostream>
#include <cstdlib>
#include <ctime> 
using namespace std;

void algo1(int A[], int n) { // n^2log(n)
    for (int i = 0; i < n; i++) {
        bool unique;
        do { 
            unique = true;
            A[i] = rand() % n + 1;
            for (int j = 0; j < i; j++) {
                if (A[i] == A[j]) {
                    unique = false; 
                    break;
                }
            }
        } while (!unique);
    }
}

void algo2 (int A[], int n) { // nlog(n)
    bool used[n] ;
    for (int i=0; i<n; i++) {
        A[i] = 0;
    }
    for (int i=0; i<n; i++) {
        used[i] = false;
    }
    for (int i=0; i<n; i++) {
        int randInt = rand()%n + 1;
        if (!used[randInt-1]) { // The probability of success is: (n-i)/n
            A[i] = randInt;     // So the expected number of iterations is: (n)/(n-i )
            used[randInt] = true;
        }
    }
}

void algo3(int A[], int n) { // O(n)
    for (int i=0; i<n; i++) {
        A[i] = i+1;
    }
    for(int i=1; i<n; i++) {
        swap(A[i], A[rand()%i]);
    }
}

void runAlgorithm(void (*algo)(int[], int), int n) {
    int* A = new int[n];
    auto start = chrono::high_resolution_clock::now();
    for (int i = 0; i < 10; i++) {
        algo(A, n);
    }
    auto end = chrono::high_resolution_clock::now();
    delete[] A;
    chrono::duration<double> duration = end - start;
    cout << "Time taken for N = " << n << ": " << duration.count() << " seconds" << endl;
}

int main() {
    srand(static_cast<unsigned int>(time(0)));

    // Algorithm 1
    int N_values1[] = {250, 500, 1000, 2000};
    cout << "Running Algorithm 1:" << endl;
    for (int n : N_values1) {
        int* A = new int[n];
        for (int i=0; i<n; i++) {
            A[i] = i+1;
        }
        auto start = chrono::high_resolution_clock::now();
        algo1(A, n);
        auto end = chrono::high_resolution_clock::now();
        delete[] A;
        cout << "N = " << n << ": " << chrono::duration<double>(end - start).count() << " seconds" << endl;
    }

    // Algorithm 2
    int N_values2[] = {25000, 50000, 100000, 200000, 400000, 800000};
    cout << "Running Algorithm 2:" << endl;
    for (int n : N_values2) {
        int* A = new int[n];
        for (int i=0; i<n; i++) {
            A[i] = i+1;
        }
        auto start = chrono::high_resolution_clock::now();
        algo2(A, n);
        auto end = chrono::high_resolution_clock::now();
        delete[] A;
        cout << "N = " << n << ": " << chrono::duration<double>(end - start).count() << " seconds" << endl;
    }

    // Algorithm 3
    int N_values3[] = {100000, 200000,400000, 800000, 1600000, 3200000, 6400000};
    cout << "Running Algorithm 3:" << endl;
    for (int n : N_values3) {
        int* A = new int[n];
        for (int i=0; i<n; i++) {
            A[i] = i+1;
        }
        auto start = chrono::high_resolution_clock::now();
        algo3(A, n);
        auto end = chrono::high_resolution_clock::now();
        delete[] A;
        cout << "N = " << n << ": " << chrono::duration<double>(end - start).count() << " seconds" << endl;
    }

    return 0;
}