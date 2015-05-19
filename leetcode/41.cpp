class Solution {
public:
    int firstMissingPositive(vector<int>& nums) {
        for (auto i = nums.begin(); i != nums.end(); ) {
            if (*i > nums.size() || *i <= 0 || *i == i - nums.begin() + 1 || *(nums.begin() + *i - 1) == *i) {
                ++i;
            } else {
                iter_swap(i, nums.begin() + *i - 1);
            }
        }
        for (auto i = nums.begin(); i != nums.end(); ++i) {
            if (*i != i - nums.begin() + 1) {
                return i - nums.begin() + 1;
            }
        }
        return nums.size() + 1;
    }
};
