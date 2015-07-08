class Solution {
public:
    int countDigitOne(int n) {
        int res = 0, tail = 0, base = 1;
        while (n > 0) {
            int cur = abs(n)%10;
            n /= 10;
            res = res + abs(n)*base;
            switch (cur) {
            case 0:
                break;
            case 1: 
                res += tail + 1;
                break;
            default:
                res += base;
                break;
            }
            tail += cur*base;
            base *= 10;
        }
        return res;
    }
};
