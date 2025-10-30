#include <iostream>
#include <pthread.h>

using namespace std;

static int my_global = 1;

void* modify_global(void* arg) {
    my_global++;  // This modification affects all threads
    return nullptr;
}

int main() {
    pthread_t thread;
    pthread_create(&thread, nullptr, modify_global, nullptr);
    pthread_join(thread, nullptr);
    

    cout << my_global << endl; // Output: 2 (because threads share memory)
    return 0;
}
