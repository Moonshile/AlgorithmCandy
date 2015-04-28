#include <stdio.h>

#define MID(arr, n) ((n)%2 == 0 ? (arr[n/2] + arr[n/2 - 1])/2 + 0.5f : (double)(arr[n/2]))

double findMedianSortedArrays(int A[], int m, int B[], int n) {
    
}


int main() {
    int A[] = {2,3};
    int B[] = {1};
    printf("%f\n", findMedianSortedArrays(A, 2, B, 1));
    return 0;
}
