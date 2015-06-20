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
    
public:
    int findMin(vector<int>& nums) {
        int max = searchMax(nums.begin(), nums.end()) - nums.begin();
        return nums[(max + 1)%nums.size()];
    }
};
