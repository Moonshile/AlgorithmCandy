#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX (200000)

int _min = MAX;

void determine(int* iloads, int* mark, int n, int i, int cur) {
    int* l = iloads + i*n, j;
    for(j = 0; j < n; j++) {
        if(mark[j] == 0) {
            cur += l[j];
            mark[j] = 1;
            if(i < n - 1 && cur < _min) {
                determine(iloads, mark, n, i + 1, cur);
            } else if (i == n - 1 && cur < _min) {
                _min = cur;
            }
            cur -= l[j];
            mark[j] = 0;
        }
    }
}

int main() {
    int n, *mark, *iloads, i;
    scanf("%d", &n);
    mark = (int*)malloc(sizeof(int)*n);
    iloads = (int*)malloc(sizeof(int)*n*n);
    memset(mark, 0, sizeof(int)*n);
    for(i = 0; i < n*n; i++) {
        scanf("%d", iloads + i);
    }
    determine(iloads, mark, n, 0, 0);
    printf("%d\n", _min);
    return 0;
}
