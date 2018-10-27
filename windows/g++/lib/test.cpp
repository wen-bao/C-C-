#include "MyMath.h"
#include <stdio.h>

int main() {
    MyMath mm;
    int sum = mm.add(1024, 1024);
    printf("%d\n", sum);
    return 0;
}