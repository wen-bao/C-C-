#include "avl.h"

int getHeight(AVLTree tree) {
    return HEIGHT(tree);
}

void preOrder(AVLTree tree) {
    if(tree != NULL) {
        printf("%d ", tree->data);
        preOrder(tree->left);
        preOrder(tree->right);
    }
}

void inOrder(AVLTree tree) {
    if(tree != NULL) {
        inOrder(tree->left);
        printf("%d ", tree->data);
        inOrder(tree->right);
    }
}

void postOrder(AVLTree tree) {
    if(tree != NULL) {
        postOrder(tree->left);
        postOrder(tree->right);
        printf("%d ", tree->data);
    }
}
/*
**************************************
Operation
**************************************
*/
static Node* create(int value, Node* leftNode, Node* rightNode) {
    Node *p;
    if((p = (Node*)malloc(sizeof(Node))) == NULL ) {
        return NULL;
    }
    p->data = value;
    p->height = 0;
    p->left = leftNode;
    p->right = rightNode;
    return p;
}

static Node* L_L_Adjust(AVLTree node) { // R_Rotation
    AVLTree node2 = node->left;

    node->left = node2->right;
    node2->right = node;

    // update height order cann't change
    node->height = MAX(HEIGHT(node->left), HEIGHT(node->right)) + 1; //Grandpa Becomes Dad -> Newdad's height = MAX(grandson) + 1
    node2->height = MAX(HEIGHT(node2->left), HEIGHT(node2->right));

    return node2;
}

static Node* R_R_Adjust(AVLTree node) { // L_Rotation
    AVLTree node2 = node->right;

    node->right = node2->left;
    node2->left = node;

    node->height = MAX(HEIGHT(node->left), HEIGHT(node->right)) + 1;
    node2->height = MAX(HEIGHT(node2->left), HEIGHT(node2->right));

    return node2;
}

static Node* L_R_Adjust(AVLTree node) { // first->(left L_Rotation)  second->(node R_Rotation)
    node->left = R_R_Adjust(node->left);
    return L_L_Adjust(node);
}

static Node* R_L_Adjust(AVLTree node) { // first->(right R_Rotation) second->(node L_Rotation)
    node->right = L_L_Adjust(node->right);
    return R_R_Adjust(node);
}

Node* avlInsert(AVLTree tree, int value) {
    if(tree == NULL) {
        tree = create(value, NULL, NULL);
        if(tree == NULL) {
            printf("ERROR: create avlTree failed!\n");
            return NULL;
        }
    } else if(value < tree->data) {
        tree->left = avlInsert(tree->left, value);
        if(HEIGHT(tree->left) - HEIGHT(tree->right) == 2) { // L__
            if(value < tree->left->data) { // L_L
                tree = L_L_Adjust(tree);
            } else { // L_R
                tree = L_R_Adjust(tree);
            }
        }
    } else if(value > tree->data){
        tree->right = avlInsert(tree->right, value);
        if(HEIGHT(tree->right) - HEIGHT(tree->left) == 2) { // R__
            if(value > tree->right->data) { // R_R
                tree = R_R_Adjust(tree);
            } else { // R_L
                tree = R_L_Adjust(tree);
            }
        }
    } else { // value == tree->data
        printf("ERROR: repeat insert!\n");
    }
    tree->height = MAX(HEIGHT(tree->left), HEIGHT(tree->right)) + 1; // update height
    return tree;
}

Node* avlSearch(AVLTree tree, int value) {
    while(tree != NULL && tree->data != value) {
        if(value < tree->data) {
            tree = tree->left;
        } else {
            tree = tree->right;
        }
    }
    return tree;
}

static Node* max_node(AVLTree tree) {
    if(tree == NULL) return NULL;
    while(tree->right != NULL) tree = tree->right;
    return tree;
}

static Node* min_node(AVLTree tree) {
    if(tree == NULL) return NULL;
    while(tree->left != NULL) tree = tree->left;
    return tree;
}

static Node* delete_node(AVLTree tree, Node* aim) {
    if(tree == NULL || aim == NULL) {
        return NULL;
    }

    if(aim->data < tree->data) {
        tree->left = delete_node(tree->left, aim);
        if(HEIGHT(tree->right) - HEIGHT(tree->left) == 2) {
            Node* rChild = tree->right;
            if(HEIGHT(rChild->left) < HEIGHT(rChild->right)) { // R_R
                tree = R_R_Adjust(tree);
            } else { // R_L
                tree = R_L_Adjust(tree);
            }
        }
    } else if(aim->data > tree->data) {
        tree->right = delete_node(tree->right, aim);
        if(HEIGHT(tree->left) - HEIGHT(tree->right) == 2) {
            Node* lChild = tree->left;
            if(HEIGHT(lChild->left) > HEIGHT(lChild->right)) { // L_L
                tree = L_L_Adjust(tree);
            } else { // L_R
                tree = L_R_Adjust(tree);
            }
        }
    } else { // find delete node
        if(tree->left && tree->right) { // left and right not empty
            if(HEIGHT(tree->left) > HEIGHT(tree->right)) { // left Higher => find upper_bound((tree->data)-1) => [tree->left->(right...)]) 
                Node* max = max_node(tree->left);
                tree->data = max->data;
                tree->left = delete_node(tree->left, max); // Equivalent to delete the node of max
            } else { // find lower_bound((tree->data)+1) => [tree->right->(left...)]
                Node* min = min_node(tree->right);
                tree->data = min->data;
                tree->right = delete_node(tree->right, min); // Equivalent to delete the node of min
            }
        } else {
            Node* tmp = tree;
            tree = tree->left ? tree->left : tree->right;
            free(tmp);
        }
    }
    return tree;
}

Node* avlDelete(AVLTree tree, int value) {
    Node* aim;
    if((aim = avlSearch(tree, value)) == NULL) {
        printf("ERROE: delete value %d not found!\n", value);
    } else {
        tree = delete_node(tree, aim);
    }
    return tree;
}

void avlDestroy(AVLTree tree) {
    if(tree == NULL) {
        return;
    }
    if(tree->left != NULL) {
        avlDestroy(tree->left);
    }
    if(tree->right != NULL) {
        avlDestroy(tree->right);
    }
    free(tree);
}