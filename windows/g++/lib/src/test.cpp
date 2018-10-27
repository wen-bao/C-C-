#include "MyMath.h"
#include <stdio.h>

int main() {
    std::vector<int> v{1, 2, 3};
    
    MyMath mm;
    int sum = mm.add(v);
    printf("%d\n", sum);
    return 0;
}