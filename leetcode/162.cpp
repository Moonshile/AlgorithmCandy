class Solution {
private:
    using citer = vector<int>::const_iterator;
    
    citer upperBound(citer begin, citer end) {
        auto len = end - begin, half = len;
        citer middle, very_begin = begin;
        while (len > 0) {
            half = len >> 1;
            middle = begin + half;
            if (middle == very_begin || *middle > *(middle - 1)) {
                begin = middle + 1;
                len = len - half - 1;
            } else {
                len = half;
            }
        }
        return begin;
    }
    
public:
    int findPeakElement(vector<int>& nums) {
        citer t = upperBound(nums.begin(), nums.end());
        return t - nums.begin() - 1;
    }
};
