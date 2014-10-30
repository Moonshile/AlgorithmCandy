#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char *read_from_stdin();
int next_int(int*);

typedef struct __node__ {
    int v;
    struct __node__* left;
    struct __node__* right;
} Node;

Node* tree;
int _node_p = 0;

Node* new_node() {
    Node* n = tree + _node_p;
    _node_p++;
    n->left = 0;
    n->right = 0;
    return n;
}

int find(int* list, int lo, int hi, int v) {
    while(lo < hi && list[lo] != v) {
        lo++;
    }
    return lo == hi ? -1 : lo;
}

Node* build(int*pre, int pre_lo, int pre_hi, int* po, int po_lo, int po_hi, Node* tree) {
    int pre_left = pre_lo + 1, pre_right, po_left, po_right = po_hi - 1;
    int l_value = pre[pre_lo + 1], r_value = po[po_hi - 2];
    tree->v = pre[pre_lo];
    if(pre_lo + 1 >= pre_hi) {
        return tree;
    }
    pre_right = find(pre, pre_lo + 2, pre_hi, r_value);
    po_left = po_lo + pre_right - pre_left - 1;
    if(pre_left < pre_right) {
        tree->left = build(pre, pre_left, pre_right, po, po_lo, po_left + 1, new_node());
    }
    if(pre_right < pre_hi) {
        tree->right = build(pre, pre_right, pre_hi, po, po_left + 1, po_right, new_node());
    }
    return tree;
}

void inorder(Node* tree) {
    if(tree) {
        inorder(tree->left);
        printf("%d ", tree->v);
        inorder(tree->right);
    }
}

int main() {
    int n, i, *preorder, *postorder;
    read_from_stdin();
    next_int(&n);
    preorder = (int*)malloc(sizeof(int)*n);
    postorder = (int*)malloc(sizeof(int)*n);
    tree = (Node*)malloc(sizeof(Node)*n);
    for(i = 0; i < n; i++) {
        next_int(preorder + i);
    }
    for(i = 0; i < n; i++) {
        next_int(postorder + i);
    }
    build(preorder, 0, n, postorder, 0, n, new_node());
    inorder(tree);
    free(preorder);
    free(postorder);
    free(tree);
    return 0;
}

#define MAX_BUF_LEN (100<<10<<10)

char fread_buf[MAX_BUF_LEN];
int fread_buf_pointer = 0;

char *read_from_stdin() {
    int len = fread(fread_buf, sizeof(char), MAX_BUF_LEN, stdin);
    fread_buf[len] = '\0';
    return fread_buf;
}

// next integer, prefix blanks will be removed
int next_int(int *res) {
    char c = fread_buf[fread_buf_pointer++];
    int is_pos = 1;
    while(!(c >= '0' && c <= '9' || c == '\0' || c == '-')) {
        c = fread_buf[fread_buf_pointer++];
    }
    if(c == '\0') {
        return 0;
    }
    if(c == '-') {
        is_pos = 0;
        c = fread_buf[fread_buf_pointer++];
    }
    *res = 0;
    while(c >= '0' && c <= '9') {
        *res = (*res)*10 + c - '0';
        c = fread_buf[fread_buf_pointer++];
    }
    if(!is_pos) {
        *res = -*res;
    }
    return c;
}
