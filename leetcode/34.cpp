class Solution {
private:
    using citer = vector<int>::const_iterator;
    
    citer upperBound(citer begin, citer end, int target) {
        auto len = end - begin, half = len;
        citer middle;
        while (len > 0) {
            half = len >> 1;
            middle = begin + half;
            if (target < *middle) {
                len = half;
            } else {
                begin = middle + 1;
                len = len - half - 1;
            }
        }
        return begin;
    }
    
    citer lowerBound(citer begin, citer end, int target) {
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
    vector<int> searchRange(vector<int>& nums, int target) {
        vector<int> res{-1, -1};
        auto upper = upperBound(nums.begin(), nums.end(), target), lower = lowerBound(nums.begin(), nums.end(), target);
        if (lower != nums.end() && *lower == target) {
            res[0] = lower - nums.begin();
            res[1] = upper - 1 - nums.begin();
        }
        return res;
    }
};
