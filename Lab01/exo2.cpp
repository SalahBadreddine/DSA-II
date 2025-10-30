#include <iostream>
#include <string>

using namespace std ;


void Permutations(string str, int a, int z) {
    if (a==z) {
        cout << str << " ";
        return ;
    }
    for (int i=a; i<=z; i++) {
        swap(str[i], str[a]);
        Permutations(str, a+1, z);
    }
}

int main()
{
    Permutations("ABCD", 0, 3);
}

// void Permutations(string str, int index) {
//     int n = str.length();
//     if (index == n) {
//         cout << str << " "; // Print the current permutation
//         return;
//     }

//     for (int i = index; i < n; i++) {
//         // Check for duplicates: only swap if the current character is not a duplicate of the previous character
//         if (i != index && str[i] == str[index]) {
//             continue; // Skip duplicates
//         }

//         swap(str[i], str[index]); // Swap the current index with i
//         Permutations(str, index + 1); // Recursively call for the next index
//         swap(str[i], str[index]); // Backtrack to restore the original string
//     }
// }