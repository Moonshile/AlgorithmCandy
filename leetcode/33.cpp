class Solution {
private:
    using citer = vector<int>::const_iterator;
    
    citer searchMax(citer begin, citer end) {
        auto len = end - begin, half = len;
        citer middle;
        while (len > 1) {
            half = len >> 1;
            middle = begin + half;
            if (*begin > *middle) {
                len = half;
            } else {
                begin = middle;
                len -= half;
            }
        }
        return begin;
    }
    
    citer lowerBound(citer begin, citer end, int value) {
        auto len = end - begin, half = len;
        citer middle;
        while (len > 0) {
            half = len >> 1;
            middle = begin + half;
            if (value <= *middle) {
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
        auto maxValue = searchMax(nums.begin(), nums.end());
        auto res = lowerBound(nums.begin(), maxValue + 1, target);
        if (res != nums.end() && *res == target) {
            return res - nums.begin();
        } else {
            res = lowerBound(maxValue + 1, nums.end(), target);
            return res != nums.end() && *res == target ? res - nums.begin() : -1;
        }
    }
};
