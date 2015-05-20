class Solution {
public:
    int maxSubArray(vector<int>& nums) {
        int res = INT_MIN, cur = 0;
        for (int i: nums) {
            cur += i;
            if (cur > res) {
                res = cur;
            }
            if (cur < 0) {
                cur = 0;
            }
        }
        return res;
    }
};
