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
    
public:
    int findMin(vector<int>& nums) {
        int max = searchLastMax(nums.begin(), nums.end()) - nums.begin();
        return nums[(max + 1)%nums.size()];
    }
};
