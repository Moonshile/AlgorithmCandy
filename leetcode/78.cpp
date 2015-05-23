class Solution {
public:
    vector<vector<int>> subsets(vector<int>& nums) {
        sort(nums.begin(), nums.end());
        vector<int> cur, tmp;
        vector<vector<int>> res{tmp};
        int i = 0;
        while (i >= 0) {
            // forwarding
            for (; i < nums.size(); ++i) {
                cur.push_back(i);
                vector<int> tmp;
                for (auto j: cur) {
                    tmp.push_back(nums[j]);
                }
                res.push_back(tmp);
            }
            // backwarding
            if (i == nums.size()) {
                cur.pop_back();
                i = cur.empty() ? -1 : cur.back() + 1;
            }
            if (!cur.empty()) {
                cur.pop_back();
            }
        }
        return res;
    }
};
