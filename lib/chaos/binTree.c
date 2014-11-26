#include <stdio.h>
#include <stdlib.h>

//****************************** binTree ******************************************************
#define EMPTY_BIN_TREE_VALUE (0)
typedef int BinTreeType;
typedef struct __bin_node__ {
    BinTreeType ele;
    struct __bin_node__* left;
    struct __bin_node__* right;
    struct __bin_node__* parent;
} BinNode;
typedef struct __bin_tree__ {
    BinNode* root;
} BinTree;
BinNode* newBinNode(BinTreeType v);
BinNode* newBinNodes(int n);
BinTree* newBinTree();
BinNode* insertValueAsLeft(BinTreeType v, BinNode* parent);
BinNode* insertValueAsRight(BinTreeType v, BinNode* parent);
BinNode* insertNodeAsLeft(BinNode* v, BinNode* parent);
BinNode* insertNodeAsRight(BinNode* v, BinNode* parent);

//****************************** binTree ******************************************************

BinNode* newBinNode(BinTreeType v) {
    BinNode* bn = (BinNode*)malloc(sizeof(BinNode));
    bn->ele = v;
    bn->left = 0;
    bn->right = 0;
    bn->parent = 0;
    return bn;
}

BinNode* newBinNodes(int n) {
    BinNode* bn = (BinNode*)malloc(sizeof(BinNode)*n);
    int i;
    for(i = 0; i < n; i++) {
        bn[i].ele = EMPTY_BIN_TREE_VALUE;
        bn[i].left = 0;
        bn[i].right = 0;
        bn[i].parent = 0;
    }
    return bn;
}

BinTree* newBinTree() {
    BinTree* bt = (BinTree*)malloc(sizeof(BinTree));
    bt->root = 0;
    return bt;
}

BinNode* insertValueAsLeft(BinTreeType v, BinNode* parent) {
    return insertNodeAsLeft(newBinNode(v), parent);
}

BinNode* insertValueAsRight(BinTreeType v, BinNode* parent) {
    return insertNodeAsRight(newBinNode(v), parent);
}

BinNode* insertNodeAsLeft(BinNode* v, BinNode* parent) {
    v->left = parent->left;
    v->parent = parent;
    parent->left = v;
    return v;
}

BinNode* insertNodeAsRight(BinNode* v, BinNode* parent) {
    v->right = parent->right;
    v->parent = parent;
    parent->right = v;
    return v;
}

//****************************** test ******************************************************

int main() {
    BinTree* bt = newBinTree();
    BinNode* bn = newBinNode(0);
    bt->root = bn;
    insertValueAsLeft(1, bn);
    bn = insertValueAsRight(2, bn);
    insertValueAsLeft(3, bn);
    bn = insertValueAsRight(4, bn);
    bn = bt->root;
    printf("%d %d %d\n", bn->ele, bn->left->ele, bn->right->ele);
    bn = bn->right;
    printf("%d %d %d\n", bn->ele, bn->left->ele, bn->right->ele);
    return 0;
}
