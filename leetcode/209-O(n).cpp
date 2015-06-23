class Solution {
public:
    int minSubArrayLen(int s, vector<int>& nums) {
        int res = INT_MAX, cur = 0;
        for (int i = -1, j = 0; j < nums.size(); ++j) {
            cur += nums[j];
            while (cur >= s) {
                res = min(res, j - i);
                cur -= nums[++i];
            }
        }
        return res%INT_MAX;
    }
};
