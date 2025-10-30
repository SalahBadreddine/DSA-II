#include <iostream>

using namespace std ;

int FlipNum (int N, int res=0) {
    res *= 10;
    res += N%10;
    if (N/10 < 1) {
        return res;
    }
    return FlipNum(N/10, res);
}

int main () 
{
    int num;
    cout << "Enter the number to flip: ";
    cin >> num ;
    cout << "The flipped number is: " << FlipNum(num) << endl;
    return 0;
}