#include <stdio.h>
#include <string.h>

typedef struct __pos__ {
    int length;
    int start;
}Position, *PositionPtr;

Position checkPalindrome(char* s, int n) {
    int odd = 1, even = 0, i = n - 1, j = n + 1;
    Position p;
    if(n == 0 && s[0] != s[1] || s[n + 1] == '\0') {
        p.length = 1;
        p.start = n;
        return p;
    }
    while(i >= 0 && s[j] != '\0' && s[i--] == s[j++]) {
        odd += 2;
    }
    i = n;
    j = n + 1;
    while(i >= 0 && s[j] != '\0' && s[i--] == s[j++]) {
        even += 2;
    }
    p.length = odd > even ? odd : even;
    p.start = odd > even ? n - odd/2 : n + 1 - even/2;
    return p;
}

char* longestPalindrome(char* s) {
    int p = 0;
    Position max, tmp;
    max.length = 0;
    if(s[0] == '\0') {
        return s;
    }
    while(s[p]) {
        tmp = checkPalindrome(s, p);
        if(tmp.length > max.length) {
            max = tmp;
        }
        p++;
    }
    printf("%d\n", max.start + max.length);
    s[max.start + max.length] = '\0';
    return s + max.start;
}

int main() {
    char s[][1000] = {"aa", "abcb", "abababababa"};
    int i;
    for (i = 0; i < 3; i++) {
        printf("%s\n", longestPalindrome(s[i]));
    }
    return 0;
}
