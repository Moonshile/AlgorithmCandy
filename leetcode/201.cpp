class Solution {
public:
    int rangeBitwiseAnd(int m, int n) {
        int res = m, cur = ((res - 1) | res) + 1;
        while (res && cur > 0 && cur <= n) {
            res &= cur;
            cur = ((res - 1) | res) + 1;
        }
        return res;
    }
};
