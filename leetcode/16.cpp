class Solution {
private:
    int twoSumClosest(vector<int>::const_iterator begin, vector<int>::const_iterator end, const int target) {
        --end;
        int res = *begin + *end;
        while (begin + 1 != end) {
            int tmp_begin = *(begin + 1) + *end, tmp_end = *begin + *(end - 1), tmp;
            if (abs(target - tmp_begin) < abs(target - tmp_end)) {
                ++begin;
                tmp = tmp_begin;
            } else {
                --end;
                tmp = tmp_end;
            }
            if (abs(target - tmp) < abs(target - res)) {
                res = tmp;
            }
        }
        return res;
    }
public:
    int threeSumClosest(vector<int>& nums, int target) {
        sort(nums.begin(), nums.end());
        int res = nums[0] + twoSumClosest(nums.begin() + 1, nums.end(), target - nums[0]);
        for (auto i = nums.begin() + 1; i != nums.end() - 2; ++i) {
            int tmp = *i + twoSumClosest(i + 1, nums.end(), target - *i);
            if (abs(target - res) > abs(target - tmp)) {
                res = tmp;
            }
        }
        return res;
    }
};
