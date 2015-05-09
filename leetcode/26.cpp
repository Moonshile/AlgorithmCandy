class Solution {
public:
    int removeDuplicates(vector<int>& nums) {
        if (nums.size() < 2) {
            return nums.size();
        }
        auto cur = nums.begin(), i = nums.begin();
        for (; i != nums.end(); ++cur) {
            *cur = *i;
            for(; i != nums.end() && *i == *cur; ++i);
        }
        for (int origin = nums.size(), now = cur - nums.begin(), i = 0; i < origin - now; ++i, nums.pop_back());
        return nums.size();
    }
};