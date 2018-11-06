#include "sort.h"

struct Node {
    int x;
    int y;
    bool operator > (const Node &m)const {
        if(x == m.x) return y > m.y;
        return x > m.x;
    }
};

using namespace MyAlg;
int main() {
    
    printf("===test sort int\n\n");
    int a[] = {99, 28, 77, 36, 55, 44, 3, 2, 1};
    sort(a, 0, 6);
    for(int i = 0; i < 9; ++i) {
        printf("%d\n", a[i]);
    }

    printf("===test sort struct\n\n");
    Node no[6] = {{1, 2}, {2, 3}, {2, 1}, {4, 3}, {-1, 2}, {2, 1}};
    sort(no, 0, 6);
    for(int i = 0; i < 6; ++i) {
        printf("%d**%d\n", no[i].x, no[i].y);
    }

    return 0;
}