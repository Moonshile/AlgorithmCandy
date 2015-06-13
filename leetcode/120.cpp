class Solution {
public:
    int minimumTotal(vector<vector<int> > &triangle) {
        vector<int> sums(triangle.size(), 0);
        int res = 0;
        for (auto &nums: triangle) {
            res = INT_MAX;
            for (int n = nums.size(), j = n - 1; j >= 0; --j) {
                sums[j] = (j == 0 ? sums[j] : (j == n - 1 ? sums[j - 1] : min(sums[j], sums[j - 1]))) + nums[j];
                res = min(res, sums[j]);
            }
        }
        return res;
    }
};
