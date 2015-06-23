class Solution {
private:
    using citer = vector<int>::const_iterator;
    
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
    int minSubArrayLen(int s, vector<int>& nums) {
        int res = INT_MAX;
        vector<int> sums;
        for (int i = 0, cur = 0; i < nums.size(); ++i) {
            cur += nums[i];
            sums.push_back(cur);
        }
        for (int i = 0; i < nums.size(); ++i) {
            auto target = lowerBound(sums.begin() + i, sums.end(), s - nums[i] + sums[i]);
            if (target < sums.end()) {
                res = min(res, static_cast<int>(target - sums.begin() - i + 1));
            }
        }
        return res%INT_MAX;
    }
};
