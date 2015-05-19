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
    int searchInsert(vector<int>& nums, int target) {
        auto lower = lowerBound(nums.begin(), nums.end(), target);
        return nums.size() == 0 ? 0 : lower - nums.begin();
    }
};
