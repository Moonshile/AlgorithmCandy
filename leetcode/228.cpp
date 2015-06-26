class Solution {
public:
    vector<string> summaryRanges(vector<int>& nums) {
        vector<string> res;
        int i = 0, j = 0, n = nums.size();
        for (; j < n; ++j) {
            if (j == n - 1 || nums[j] + 1 != nums[j + 1]) {
                stringstream ss;
                ss << nums[i];
                if (j > i) {
                    ss << "->" << nums[j];
                }
                i = j + 1;
                res.push_back(ss.str());
            }
        }
        return res;
    }
};
