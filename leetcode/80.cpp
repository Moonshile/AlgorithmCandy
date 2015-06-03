class Solution {
public:
    int removeDuplicates(vector<int>& nums) {
        int i = 0, j = 1, m = nums.size();
        for (; j < m; ++j) {
            if (!(nums[j] == nums[i] && i > 0 && nums[i] == nums[i - 1])) {
                nums[++i] = nums[j];
            }
        }
        for (++i; i < m; ++i) {
            nums.pop_back();
        }
        return nums.size();
    }
};
