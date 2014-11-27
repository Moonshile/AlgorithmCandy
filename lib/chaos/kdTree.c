#include <stdio.h>
#include <stdlib.h>

typedef int KdTreeType;
#define K_KD_TREE (2)
typedef struct __kd_element__ KdElement;

typedef struct __bin_node__ BinNode;
typedef KdElement* BinTreeType;
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

//****************************** kdTree ******************************************************
typedef BinNode KdNode;
typedef BinTree KdTree;
#define newKdTree newBinTree
#define newKdNode newBinNode
#define newKdNodes newBinNodes
#define freeKdTree freeBinTree
struct __kd_element__ {
    KdTreeType* v;
    int level;
    int lowerCount;
    int greaterCount;
};
KdElement* newKdElement(KdTreeType* v, int level);
KdNode* findInKdTree(KdTree* kt, KdTreeType* v, int (*cmp)(const void*, const void*));
KdNode* insertIntoKdTree(KdTree* kt, KdTreeType* v, int (*cmp)(const void*, const void*));
int rangeSearch(KdTree* kt, KdTreeType* lo, KdTreeType* hi, int (*cmp)(const void*, const void*), void (*visit)(KdNode*));

//****************************** kdTree ******************************************************

KdElement* newKdElement(KdTreeType* v, int level) {
    KdElement* ke = (KdElement*)malloc(sizeof(KdElement));
    ke->v = v;
    ke->level = level;
    ke->lowerCount = 0;
    ke->greaterCount = 0;
    return ke;
}

KdNode* findInKdTree(KdTree* kt, KdTreeType* v, int (*cmp)(const void*, const void*)) {
    KdNode* kn = kt->root, *ret = 0;
    while(kn) {
        ret = kn;
        kn = cmp(&(v[ret->ele->level]), &(kn->ele->v[ret->ele->level])) < 0 ? kn->left : kn->right;
    }
    return ret;
}

KdNode* insertIntoKdTree(KdTree* kt, KdTreeType* v, int (*cmp)(const void*, const void*)) {
    KdNode* parent = findInKdTree(kt, v, cmp);
    if(parent) {
        int pl = parent->ele->level, level = pl + 1 >= K_KD_TREE ? 0 : pl + 1;
        if(cmp(&(v[pl]), &(parent->ele->v[pl])) < 0) {
            insertValueAsLeft(newKdElement(v, level), parent);
        } else {
            insertValueAsRight(newKdElement(v, level), parent);
        }
    } else {
        kt->root = newKdNode(newKdElement(v, 0));
    }
    return parent;
}

int rangeAlongLeft(Stack* s, KdNode* kn, KdTreeType* lo, KdTreeType* hi, int (*cmp)(const void*, const void*), void (*visit)(KdNode*)) {
    int ret = 0;
    while(kn) {
        int inRange = 1, i;
        for(i = 0; i < K_KD_TREE; i++) {
            inRange = inRange && cmp(lo + i, kn->ele->v + i) <= 0 && cmp(kn->ele->v + i, hi + i) <= 0;
        }
        if(inRange) {
            visit(kn);
            ret++;
        }
        if(kn->right && cmp(kn->ele->v + kn->ele->level, hi + kn->ele->level) <= 0) {
            push(s, kn->right);
        }
        kn = cmp(lo + kn->ele->level, kn->ele->v + kn->ele->level) <= 0 ? kn->left : 0;
    }
    return ret;
}

int rangeSearch(KdTree* kt, KdTreeType* lo, KdTreeType* hi, int (*cmp)(const void*, const void*), void (*visit)(KdNode*)) {
    int count = 0;
    if(kt->root) {
        Stack* s = newStack(kt->root->height << 1);
        count += rangeAlongLeft(s, kt->root, lo, hi, cmp, visit);
        while(!isEmptyStack(s)) {
            count += rangeAlongLeft(s, pop(s), lo, hi, cmp, visit);
        }
        freeStack(s);
    }
    return count;
}

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

int compare(const void* x, const void* y) {
    return *(KdTreeType*)x - *(KdTreeType*)y;
}

void visit(KdNode* kn) {
    if(kn) {
        int i;
        printf("V:");
        for(i = 0; i < K_KD_TREE; i++) {
            printf("%d-", kn->ele->v[i]);
        }
        printf(", L:%d, H:%d, S:%d\n", kn->ele->level, kn->height, kn->size);
    } else {
        printf("-\n");
    }
}

int main() {
    KdTree* kt = newKdTree();
    int i = 0, n, vs[] = {0, 1, 4, 5, 3, 2, 9, 7, 8, 6}, s[] = {4, 5, 9, 7};
    KdNode* kn;
    insertIntoKdTree(kt, vs + i, &compare);
    i += 2;
    insertIntoKdTree(kt, vs + i, &compare);
    i += 2;
    insertIntoKdTree(kt, vs + i, &compare);
    i += 2;
    insertIntoKdTree(kt, vs + i, &compare);
    i += 2;
    insertIntoKdTree(kt, vs + i, &compare);
    preorderTraverse(kt, &visit);
    printf("rangeSearch (4,5)-(9,7) \n");
    printf("count: %d\n", rangeSearch(kt, s, s + 2, &compare, &visit));
    freeKdTree(kt);
    return 0;
}
