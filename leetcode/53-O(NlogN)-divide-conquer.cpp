class Solution {
private:
    using citer = vector<int>::const_iterator;
    int maxSubArrayDo(citer begin, citer end) {
        if (begin + 1 == end) {
            return *begin;
        }
        auto half = (end - begin)>>1;
        int maxPre = maxSubArrayDo(begin, begin + half), maxPost = maxSubArrayDo(begin + half, end);
        int pre = *(begin + half - 1), mpre = pre, post = *(begin + half), mpost = post;
        for (auto i = begin + half - 2; i >= begin; --i) {
            pre += *i;
            mpre = pre > mpre ? pre : mpre;
        }
        for (auto i = begin + half + 1; i < end; ++i) {
            post += *i;
            mpost = post > mpost ? post : mpost;
        }
        int mid = mpre > 0 && mpost > 0 ? mpre + mpost : max(mpre, mpost);
        return max(max(maxPre, maxPost), mid);
    }
public:
    int maxSubArray(vector<int>& nums) {
        return maxSubArrayDo(nums.begin(), nums.end());
    }
};
