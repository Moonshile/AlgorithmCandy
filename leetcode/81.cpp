class Solution {
private:
    using citer = vector<int>::const_iterator;
    
    citer searchMax(citer begin, citer end) {
        auto len = end - begin, half = len >> 1;
        citer middle = begin + half;
        if (len <= 1) {
            return begin;
        } else if (*begin > *middle) {
            return searchMax(begin, middle);
        } else if (*begin < *middle) {
            return searchMax(middle, end);
        } else {
            auto left = searchMax(begin, middle), right = searchMax(middle, end);
            return *left > *right ? left : right;
        }
    }
    
    citer searchLastMax(citer begin, citer end) {
        auto max = searchMax(begin, end);
        while (begin + 1 != end && *(begin + 1) == *max) {
            ++begin;
        }
        return *begin == *max ? begin : max;
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
    bool search(vector<int>& nums, int target) {
        if (nums.size() == 0) {
            return false;
        }
        auto maxValue = searchLastMax(nums.begin(), nums.end());
        auto res = lowerBound(nums.begin(), maxValue + 1, target);
        if (res != nums.end() && *res == target) {
            return true;
        } else {
            res = lowerBound(maxValue + 1, nums.end(), target);
            return res != nums.end() && *res == target;
        }
    }
};
