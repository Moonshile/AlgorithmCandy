class Solution {
public:
    int climbStairs(int n) {
        int pre = 1, next = 1;
        for (int index = 2; index <= n; ++index) {
            next += pre;
            pre = next - pre;
        }
        return next;
    }
};
