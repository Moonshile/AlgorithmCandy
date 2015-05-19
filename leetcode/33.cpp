class Solution {
private:
    using citer = vector<int>::const_iterator;
    
    citer findMax(citer begin, citer end) {
        auto len = end - begin, half = len;
        citer middle;
        while (len > 1) {
            half = len >> 1;
            middle = begin + half;
            if (*begin <= *middle) {
                begin = middle;
            }
            len -= half;
        }
        return begin;
    }
    
    citer binSearch(citer begin, citer end, int target) {
        auto len = end - begin, half = len;
        citer middle;
        while (len > 0) {
            half = len >> 1;
            middle = begin + half;
            if (target <= *middle) {
                len = half;
            } else {
                begin = middle + 1;
                len = len - half - 1;
            }
        }
        return begin;
    }
    
public:
    int search(vector<int>& nums, int target) {
        if (nums.size() < 1) {
            return -1;
        }
        auto max = findMax(nums.begin(), nums.end());
        auto t = target >= nums[0] ? binSearch(nums.begin(), max + 1, target) : binSearch(max + 1, nums.end(), target);
        return target >= nums[0] && t == max + 1 || t == nums.end() || *t != target ? -1 : t - nums.begin();
    }
};
