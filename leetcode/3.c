#include <stdio.h>
#include <string.h>

int lengthOfLongestSubstring(char* s) {
    int read[256], p = 0, cur = 0, max = -1;
    memset(read, -1, sizeof(int)*256);
    while(s[cur]) {
        if(read[s[cur]] >= p) {
            max = max > cur - p ? max : cur - p;
            p = read[s[cur]] + 1;
        }
        read[s[cur]] = cur;
        cur++;
    }
    return max > cur - p ? max : cur - p;
}

int main() {
    char* strings[] = {"abba", "a", "aa", "ab", "abcadbeb", "bbbb"};
    int i;
    for(i = 0; i < 6; i++) {
        printf("%d\n", lengthOfLongestSubstring(strings[i]));
    }
    return 0;
}