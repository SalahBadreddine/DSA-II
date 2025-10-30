#include <iostream>
#include <string>

using namespace std ;


void Permutations(string remaining, string perm="") {
    int n = remaining.length();
    // base case
    if (n==0) {
        cout << perm << " " ;
        return ;
    }
    for (int i=0; i<n; i++) {
        string temp = remaining;
        temp.erase(i, 1);
        Permutations(temp, perm+remaining[i]);
    }
}

int main()
{
    Permutations("ABCD");
}