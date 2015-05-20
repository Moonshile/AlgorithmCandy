class Solution {
private:
    vector<vector<int>> twoSumDo(vector<int> &nums, int start, int end, int target) {
        vector<vector<int>> res;
        int first = start, last = end - 1;
        while (first < last) {
            int fv = nums[first], lv = nums[last], sum = fv + lv;
            if (sum == target) {
                vector<int> a{fv, lv};
                res.push_back(a);
                ++first;
                --last;
            } else {
                sum < target ? ++first : --last;
            }
            for (; first != start && nums[first] == nums[first - 1]; ++first) {}
            for (; last != end - 1 && nums[last] == nums[last + 1]; --last) {}
        }
        return res;
    }

    vector<vector<int>> kSumDo(vector<int> &nums, int start, int end, int target, int k) {
        if (k <= 2) {
            return twoSumDo(nums, start, end, target);
        } else {
            vector<vector<int>> res;
            for (int i = start; i != end;) {
                int iv = nums[i];
                auto tmp = kSumDo(nums, i + 1, end, target - iv, k - 1);
                for (auto t: tmp) {
                    t.insert(t.begin(), iv);
                    res.push_back(t);
                }
                for (; i != end && nums[i] == iv; ++i) {}
            }
            return res;
        }
    }
    
public:
    vector<vector<int> > threeSum(vector<int> &nums) {
        sort(nums.begin(), nums.end());
        return kSumDo(nums, 0, nums.size(), 0, 3);
    }
};
