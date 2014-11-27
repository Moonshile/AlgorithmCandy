#include <stdio.h>
#include <stdlib.h>

typedef struct __bin_node__ BinNode;
typedef int BinTreeType;
#define EMPTY_BIN_TREE_VALUE (0)

typedef BinNode* StackType;
#define EMPTY_STACK_VALUE (0);

//****************************** binTree ******************************************************
struct __bin_node__ {
    BinTreeType ele;
    int height;
    int size;
    struct __bin_node__* left;
    struct __bin_node__* right;
    struct __bin_node__* parent;
};
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
void freeBinTree(BinTree* bt);
void updateHeightAndSize(BinNode* bn);
void preorderTraverse(BinTree* bt, void (*visit)(BinNode*));
void inorderTraverse(BinTree* bt, void (*visit)(BinNode*));
void postorderTraverse(BinTree* bt, void (*visit)(BinNode*));

//****************************** stack ******************************************************
typedef struct __stack__ {
    StackType* container;
    int top;
    int capacity;
} Stack;
Stack* newStack(int capacity);
int isEmptyStack(Stack* s);
void push(Stack* s, StackType v);
StackType pop(Stack* s);
StackType top(Stack* s);
void freeStack(Stack* s);

//****************************** binTree ******************************************************

BinNode* newBinNode(BinTreeType v) {
    BinNode* bn = (BinNode*)malloc(sizeof(BinNode));
    bn->ele = v;
    bn->height = 0;
    bn->size = 1;
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
        bn[i].height = 0;
        bn[i].size = 1;
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
    updateHeightAndSize(v);
    return v;
}

BinNode* insertNodeAsRight(BinNode* v, BinNode* parent) {
    v->right = parent->right;
    v->parent = parent;
    parent->right = v;
    updateHeightAndSize(v);
    return v;
}

void updateHeightAndSize(BinNode* bn) {
    bn->height = 0;
    bn->size = 1;
    if(bn->left) {
        bn->height = bn->left->height + 1;
        bn->size += bn->left->size;
    }
    if(bn->right) {
        if(bn->height < bn->right->height + 1) {
            bn->height = bn->right->height + 1;
        }
        bn->size += bn->right->size;
    }
    if(bn->parent) {
        updateHeightAndSize(bn->parent);
    }
}

void preAlongLeft(Stack* s, BinNode* bn, void (*visit)(BinNode*)) {
    while(bn) {
        visit(bn);
        if(bn->right) {
            push(s, bn->right);
        }
        bn = bn->left;
    }
}

void preorderTraverse(BinTree* bt, void (*visit)(BinNode*)) {
    if(bt->root) {
        Stack* s = newStack(bt->root->height << 1);
        preAlongLeft(s, bt->root, visit);
        while(!isEmptyStack(s)) {
            preAlongLeft(s, pop(s), visit);
        }
        freeStack(s);
    }
}

void inAlongLeft(Stack* s, BinNode* bn) {
    while(bn) {
        if(bn->right) {
            push(s, bn->right);
        }
        push(s, bn);
        bn = bn->left;
    }
}

void inorderTraverse(BinTree* bt, void (*visit)(BinNode*)) {
    if(bt->root) {
        Stack* s = newStack(bt->root->height << 1);
        BinNode* bn = 0;
        inAlongLeft(s, bt->root);
        while(!isEmptyStack(s)) {
            bn = pop(s);
            if(!(bn->right) || bn->right == top(s)) {
                visit(bn);
            } else {
                inAlongLeft(s, bn);
            }
        }
        freeStack(s);
    }
}

void postAlongLeft(Stack* s, BinNode* bn) {
    while(bn) {
        push(s, bn);
        bn = bn->left;
    }
}

void postorderTraverse(BinTree* bt, void (*visit)(BinNode*)) {
    if(bt->root) {
        Stack* s = newStack(bt->root->height << 1);
        BinNode* bn = 0;
        postAlongLeft(s, bt->root);
        while(!isEmptyStack(s)) {
            if(bn != top(s)->right && top(s)->right) {
                postAlongLeft(s, top(s)->right);
            } else {
                bn = pop(s);
                visit(bn);
            }
        }
        freeStack(s);
    }
}

void freeBinTree(BinTree* bt) {
    postorderTraverse(bt, (void (*)(BinNode*))&free);
    free(bt);
}

//****************************** stack ******************************************************

Stack* newStack(int capacity) {
    Stack* s = (Stack*)malloc(sizeof(Stack));
    s->container = (StackType*)malloc(sizeof(StackType)*capacity);
    s->top = 0;
    s->capacity = capacity;
    return s;
}

int isEmptyStack(Stack* s) {
    return s->top == 0;
}

void push(Stack* s, StackType v) {
    if(s->top < s->capacity) {
        s->container[s->top++] = v;
    }
}

StackType pop(Stack* s) {
    if(s->top > 0) {
        return s->container[--(s->top)];
    }
    return EMPTY_STACK_VALUE;
}

StackType top(Stack* s) {
    return s->top > 0 ? s->container[s->top - 1] : EMPTY_STACK_VALUE;
}

void freeStack(Stack* s) {
    free(s->container);
    free(s);
}

//****************************** test ******************************************************

void visit(BinNode* bn) {
    if(bn) {
        printf("V:%d, H:%d, S: %d\n", bn->ele, bn->height, bn->size);
    } else {
        printf("-\n");
    }
}

int main() {
    BinTree* bt = newBinTree();
    BinNode* bn = newBinNode(0);
    bt->root = bn;
    insertValueAsLeft(1, bn);
    bn = insertValueAsRight(2, bn);
    insertValueAsLeft(3, bn);
    bn = insertValueAsRight(4, bn);
    postorderTraverse(bt, &visit);
    printf("---------\n");
    preorderTraverse(bt, &visit);
    printf("---------\n");
    inorderTraverse(bt, &visit);
    freeBinTree(bt);
    return 0;
}
