#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//****************************** fast io ****************************************
// return the input buffer
char *reset_io();
int next_int(int*);

typedef struct __node__ {
    int v;
    struct __node__* left;
    struct __node__* right;
} Node;

Node* new_node() {
    Node* n = (Node*)malloc(sizeof(Node));
    n->left = 0;
    n->right = 0;
}

int build(int*pre, int*plo, int n, int* in, int ilo, int ihi, Node* tree) {
    int i, a = 0, b = 0;
    if(*plo >= n) {
        return 0;
    }
    for(i = ilo; i < ihi; i++) {
        if(in[i] == pre[*plo]) {
            break;
        }
    }
    if(i >= ihi) {
        return 1;
    }
    tree->v = pre[*plo];
    *plo += 1;
    if(ilo < i) {
        tree->left = new_node();
        a = build(pre, plo, n, in, ilo, i, tree->left);
    }
    if(i + 1 < ihi) {
        tree->right = new_node();
        b = build(pre, plo, n, in, i + 1, ihi, tree->right);
    }
    return a + b;
}

void postorder(Node* tree) {
    if(tree) {
        postorder(tree->left);
        postorder(tree->right);
        printf("%d ", tree->v);
    }
}

int main() {
    int n, i, plo = 0, *preorder, *inorder;
    Node* tree = new_node();
    reset_io();
    next_int(&n);
    preorder = (int*)malloc(sizeof(int)*n);
    inorder = (int*)malloc(sizeof(int)*n);
    for(i = 0; i < n; i++) {
        next_int(preorder + i);
    }
    for(i = 0; i < n; i++) {
        next_int(inorder + i);
    }
    plo = build(preorder, &plo, n, inorder, 0, n, tree);
    if(plo) {
        printf("-1");
    } else {
        postorder(tree);
    }
    free(preorder);
    free(inorder);
    return 0;
}

//****************************** fast io ****************************************
#define IN_BUF_LEN (100<<10<<10)
#define OUT_BUF_SIZE (10<<20)

char fread_buf[IN_BUF_LEN];
int fread_buf_pointer = 0;
char outbuf[OUT_BUF_SIZE];

char *reset_io() {
    int len = fread(fread_buf, sizeof(char), IN_BUF_LEN, stdin);
    fread_buf[len] = '\0';
    setvbuf(stdout, outbuf, _IOFBF, OUT_BUF_SIZE);
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
