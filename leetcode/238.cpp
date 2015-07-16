class Solution {
public:
    vector<int> productExceptSelf(vector<int>& nums) {
        vector<int> res(nums.size(), 1);
        if (nums.empty()) {
            return res;
        }
        int tmp = 1;
        for (size_t i = 0; i != nums.size() - 1; ++i) {
            tmp *= nums[i];
            res[i + 1] *= tmp;
        }
        tmp = 1;
        for (size_t i = nums.size() - 1; i != 0; --i) {
            tmp *= nums[i];
            res[i - 1] *= tmp;
        }
        return res;
    }
};
