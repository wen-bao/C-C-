#ifndef _AVL_H_
#define _AVL_H_

#include <stdio.h>
#include <malloc.h>

#define HEIGHT(p) (p == NULL ? -1 : ((Node*)p)->height)
#define MAX(a, b) a > b ? a : b

typedef struct AVL_TREE {
    int data;
    int height;
    struct AVL_TREE *left;
    struct AVL_TREE *right;
}Node, *AVLTree;

int getHeight(AVLTree tree);

void preOrder(AVLTree tree);

void inOrder(AVLTree tree);

void postOrder(AVLTree tree);

Node* avlSearch(AVLTree tree, int value);

Node* avlInsert(AVLTree tree, int value);

Node* avlDelete(AVLTree tree, int value);

void avlDestroy(AVLTree tree);
#endif //! _AVL_H_