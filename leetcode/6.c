#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define CEIL(n, x) ((n)%(x) == 0 ? (n)/(x) : (n)/(x) + 1)
#define PUT_IF_EXISTS(p, s, len, pos) {\
    if(pos < len) {\
        *(p++) = s[pos];\
    }\
}

char* convert(char* s, int numRows) {
    int len = strlen(s), unitSize = numRows == 1 ? 1 : numRows-1 << 1, unitCount = CEIL(len, unitSize), i, j;
    char* res = (char*)malloc(sizeof(char)*(len + 1)), *p =  res;
    for(i = 0; i < numRows; i++) {
        for(j = 0; j < unitCount; j++) {
            if(i == 0 || i == numRows - 1) {
                PUT_IF_EXISTS(p, s, len, j*unitSize + i);
            } else {
                PUT_IF_EXISTS(p, s, len, j*unitSize + i);
                PUT_IF_EXISTS(p, s, len, (j + 1)*unitSize - i);
            }
        }
    }
    *p = '\0';
    return res;
}

int main() {
    char s[][1000] = {"PAYPALISHIRING", "", "Apalindromeisaword,phrase,number,orothersequenceofunitsthatcanbereadthesamewayineitherdirection,withgeneralallowancesforadjustmentstopunctuationandworddividers.",
        "123", "1234", "glzamzp"};
    int rows[] = {3, 1, 2, 
        2, 2, 5};
    int i;
    for(i = 0; i < 6; i++) {
        printf("%s\n", convert(s[i], rows[i]));
    }
    return 0;
}
