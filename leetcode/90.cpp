class Solution {
public:
    vector<vector<int>> subsetsWithDup(vector<int>& nums) {
        sort(nums.begin(), nums.end());
        vector<int> cur, tmp;
        vector<vector<int>> res{tmp};
        int i = nums.size() > 0 ? 0 : -1;
        while (i >= 0) {
            // forwarding
            for (; i < nums.size(); ++i) {
                cur.push_back(i);
                vector<int> tmp;
                for (int j: cur) {
                    tmp.push_back(nums[j]);
                }
                // success
                res.push_back(tmp);
            }
            // backwarding
            while (i == nums.size()) {
                cur.pop_back();
                i = cur.empty() ? -1 : cur.back() + 1;
                while (i > 0 && nums[i] == nums[i - 1]) {
                    ++i;
                }
            }
            if (!cur.empty()) {
                cur.pop_back();
            }
        }
        return res;
    }
};
