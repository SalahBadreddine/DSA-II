#include <iostream>
#include <list>

using namespace std;

template<class T>
list<T> Union (list<T> l1, list<T> l2) {
    list<T> result;
    auto it1 = l1.begin();
    auto it2 = l2.begin();
    while (it1 != l1.end() && it2 != l2.end()) {
        if (*it1 < *it2) {
            result.push_back(*it1);
            it1++;
        } else if (*it2 < *it1) {
            result.push_back(*it2)
            it2++;
        } else {
            result.push_back(*it1);
            it1++;
            it2++;
        }
    }
    // Remaining from l1
    while (it1 != l1.end()) {
        result.push_back(it1);
        it1++;
    }
    // Remaining from l2
    while(it2 != l2.end()) {
        result.push_back(it2);
        it2++;
    }
    return result;
}