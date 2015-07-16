class Solution {
public:
    vector<int> productExceptSelf(vector<int>& nums) {
        vector<int> res(nums.size(), 1);
        int tmp = 1;
        for (int i = 0; i < static_cast<int>(nums.size()) - 1; ++i) {
            tmp *= nums[i];
            res[i + 1] *= tmp;
        }
        tmp = 1;
        for (int i = static_cast<int>(nums.size()) - 1; i > 0; --i) {
            tmp *= nums[i];
            res[i - 1] *= tmp;
        }
        return res;
    }
};
