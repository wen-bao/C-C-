#include "avl.h"

int main() {
    int a[] = {3, 1, 4, 1, 5, 9, 2, 6, 53, 58, 97, 93, 23, 84, 62, 64, 338, 327, 950, 288, 419, 716, 939, 937, 510, 5820, 9749, 44};
    int len = sizeof(a) / sizeof(int), i;

    AVLTree root = NULL;

    printf("height is %d\n", getHeight(root));
    for(i = 0; i < len; ++i) {
        root = avlInsert(root, a[i]);
    }
    printf("height is %d\n", getHeight(root));
    printf("pre-order==>\n");
    preOrder(root);
    printf("\n");

    Node* tmp = avlSearch(root, 4);
    if(tmp == NULL) {
        printf("Not Found!\n");
    }

    avlDelete(root, 404);
    avlDelete(root, 4);

    printf("pre-order==>\n");
    preOrder(root);
    printf("\n");

    avlDestroy(root);
    return 0;
}