/* 
1/.

1- O(n)
2- O(n2)
3- O(n3)
4- O(n(n-1)/2) = O(n2)
5- O(n5)
6- O(n4)

2/.
*/

#include <iostream>
#include<cstdlib>
#include <chrono>
using namespace std;

int func1(int n) {
    int sum=0;
    for(int i=0; i<n; ++i) {
        ++sum;
    }
    return sum;
}

int func2(int n) {
    int sum=0;
    for(int i=0; i<n; ++i) {
        for(int j=0; j<n; ++j) {
            ++sum;
        }
    }
    return sum;
}

int func3(int n) {
    int sum=0;
    for(int i=0; i<n; i++) {
        for(int j=0; j<n*n; j++) {
            ++sum;
        }
    }
    return sum;
}

int func4(int n) {
    int sum=0;
    for(int i=0; i<n; ++i) {
        for(int j=0; j<i; ++j) {
            ++sum;
        }
    }
    return sum;
}

int func5(int n) {
    int sum=0;
    for(int i=0; i<n; i++) {
        for(int j=0; j<i*i; j++) {
            for(int k=0; k<j; ++k) {
                ++sum;
            }
        }
    }
    return sum;
}

int func6(int n) {
    int sum=0;
    for(int i=1; i<n; i++) {
        for(int j=1; j<i*i; j++) {
            if(j%i == 0) {
                for(int k=0; k<j; ++k) {
                    ++sum;
                }
            }
        }
    }
    return sum;
}

int main()
{
    cout << "First function: " << endl;
    int N_values[5] = {1, 10, 100, 500, 2000};
    for (int i=0; i<5; i++) {
        auto start = chrono::high_resolution_clock::now();
        func1(N_values[i]);
        auto end = chrono::high_resolution_clock::now();
        chrono::duration<double> duration = end - start;
        cout << "The actual running time of the func1 for N = " << N_values[i] << " is: " << duration.count() << "s" << endl;
    }
    cout << endl;
    cout << "Second function: " << endl;
    for (int i=0; i<5; i++) {
        auto start = chrono::high_resolution_clock::now();
        func2(N_values[i]);
        auto end = chrono::high_resolution_clock::now();
        chrono::duration<double> duration = end - start;
        cout << "The actual running time of the func2 for N = " << N_values[i] << " is: " << duration.count() << "s" << endl;
    }
    cout << endl;
    cout << "Third function: " << endl;
    for (int i=0; i<5; i++) {
        auto start = chrono::high_resolution_clock::now();
        func3(N_values[i]);
        auto end = chrono::high_resolution_clock::now();
        chrono::duration<double> duration = end - start;
        cout << "The actual running time of the func3 for N = " << N_values[i] << " is: " << duration.count() << "s" << endl;
    }
    cout << endl;
    cout << "Fourth function: " << endl;
    for (int i=0; i<5; i++) {
        auto start = chrono::high_resolution_clock::now();
        func4(N_values[i]);
        auto end = chrono::high_resolution_clock::now();
        chrono::duration<double> duration = end - start;
        cout << "The actual running time of the func4 for N = " << N_values[i] << " is: " << duration.count() << "s" << endl;
    }
    cout << endl;
    cout << "Fifth function: " << endl;
    for (int i=0; i<5; i++) {
        auto start = chrono::high_resolution_clock::now();
        func5(N_values[i]);
        auto end = chrono::high_resolution_clock::now();
        chrono::duration<double> duration = end - start;
        cout << "The actual running time of the func5 for N = " << N_values[i] << " is: " << duration.count() << "s" << endl;
    }
    cout << endl;
    cout << "Sixth function: " << endl;
    for (int i=0; i<5; i++) {
        auto start = chrono::high_resolution_clock::now();
        func6(N_values[i]);
        auto end = chrono::high_resolution_clock::now();
        chrono::duration<double> duration = end - start;
        cout << "The actual running time of the func6 for N = " << N_values[i] << " is: " << duration.count() << "s" << endl;
    }
    return 0;

}