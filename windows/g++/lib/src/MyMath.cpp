#include "MyMath.h"

int MyMath::add(std::vector<int> v) {
    int sum = 0;
    for(auto i : v) {
        sum += i;
    }
    return sum;
}