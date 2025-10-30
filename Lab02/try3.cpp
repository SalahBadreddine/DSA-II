#include <unistd.h>
#include <iostream>

using namespace std;

int main() 
{
    for (int i=1; i<4; i++) {
        fork();
        cout << "Hi" << endl;
    }
    return 0;
}

// P1 -> 2 P2 -> 2 P3 -> 1 P4 -> 1 
// so in total it will be printed 6 times 