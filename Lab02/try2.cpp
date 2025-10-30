#include <iostream>

using namespace std;

void func1 () {
    cout << "Hello world !" << endl;
}

void func2() ;

int main() {
    func1();
    func2();
}

void func2() {
    cout << "Hello again ... " << endl;
}