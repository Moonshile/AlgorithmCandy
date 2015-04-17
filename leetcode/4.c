#include <stdio.h>

void print(int A[], int m, int B[], int n, int small, int large) {
    int i;
    printf("A = {");
    for(i = 0; i < m; i++) {
        printf("%d ", A[i]);
    }
    printf("}, B = {");
    for(i = 0; i < n; i++) {
        printf("%d ", B[i]);
    }
    printf("}\nsmall: %d, large: %d\n", small, large);
}

#define TRUE (1)
#define FALSE (0)
#define CMP (delete_min ? A[*k1] < B[*k2] : A[*k1] > B[*k2])
double findMedianSortedArrays(int A[], int m, int B[], int n) {
    int ai = 0, aj = m - 1, bi = 0, bj = n - 1, a_rest = m, b_rest = n, delete_min = TRUE, *k1, *k2;
    int small = m && A[0] < B[0] ? A[0] : B[0], large = m && A[aj] > B[bj] ? A[aj] : B[bj], *c;
    while(a_rest + b_rest > ((m + n)%2 == 1 ? 1 : 2)) {
        k1 = delete_min ? &ai : &aj;
        k2 = delete_min ? &bi : &bj;
        c = delete_min ? &small : &large;
        if(ai <= aj && bi <= bj && CMP || bi > bj) {
            *k1 += delete_min ? 1 : -1;
            a_rest--;
        } else {
            *k2 += delete_min ? 1 : -1;
            b_rest--;
        }
        if(ai <= aj && bi <= bj) {
            *c = CMP ? A[*k1] : B[*k2];
        } else if(ai <= aj) {
            *c = delete_min ? A[ai] : A[aj];
        } else {
            *c = delete_min ? B[bi] : B[bj];
        }
        delete_min = !delete_min;
    }
    return (small + large)/2.;
}

int main() {
    int A[] = {2,3};
    int B[] = {1};
    printf("%f\n", findMedianSortedArrays(A, 2, B, 1));
    return 0;
}