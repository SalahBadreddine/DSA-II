#include <iostream>

using namespace std ;

int NumberOf1 (int N) {
    if (N==0) {
        return 0;
    }
    if (N==1) {
        return 1;
    }
    if (N%2 == 0) { // The number is even
        return NumberOf1(N/2);
    } else {
        return NumberOf1(N/2) + 1;
    }
}


int main ()
{
    int num;
    cout << "Enter your number: ";
    cin >> num;
    cout << "The number of ones in the binary representation of the number is: " << NumberOf1(num) << endl;
    return 0;
}