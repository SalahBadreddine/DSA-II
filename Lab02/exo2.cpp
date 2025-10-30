#include <iostream>
#include <cmath>

using namespace std;

bool isPrime(int N) {
    if (N==1) {
        return false;
    }
    if (N==2) {
        return true;
    }
    for (int i=2; i<sqrt(N)+1; i++) { // The worst case is sqrt(N) iterations
        if (N%i == 0) {
            return false;
        }
    }
    return true;
}

int main()
{
    int num;
    cout << "Enter your number: ";
    cin >> num;
    cout << "The number " << num << " is " << (isPrime(num) ? "Prime" : "not Prime") << endl;
    return 0;
}
