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
    
    vector<vector<int>> threeSumDo(vector<int> &nums, int start, int end, int target) {
        vector<vector<int>> res;
        for (int i = start; i != end;) {
            int iv = nums[i];
            auto tmp = twoSumDo(nums, i + 1, end, target - iv);
            for (auto t: tmp) {
                t.insert(t.begin(), iv);
                res.push_back(t);
            }
            for (; i != end && nums[i] == iv; ++i) {}
        }
        return res;
    }

    vector<vector<int>> fourSumDo(vector<int> &nums, int start, int end, int target) {
        vector<vector<int>> res;
        for (int i = start; i != end;) {
            int iv = nums[i];
            auto tmp = threeSumDo(nums, i + 1, end, target - iv);
            for (auto t: tmp) {
                t.insert(t.begin(), iv);
                res.push_back(t);
            }
            for (; i != end && nums[i] == iv; ++i) {}
        }
        return res;
    }
    
public:
    vector<vector<int> > fourSum(vector<int> &nums, int target) {
        sort(nums.begin(), nums.end());
        return fourSumDo(nums, 0, nums.size(), target);
    }
};
