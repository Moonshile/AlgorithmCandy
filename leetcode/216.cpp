class Solution {
private:
    static constexpr int maxNum() { return 9; }
    
    void dfs(int k, int n, int next, int cur, vector<int> nums, vector<vector<int>> &res) {
        if (k == 0 && n == 0) {
            res.push_back(nums);
            return;
        }
        if (k*maxNum() < n) {
            return;
        }
        for (int i = next; i <= maxNum() && i <= n; ++i) {
            nums.push_back(i);
            dfs(k - 1, n - i, i + 1, cur + i, nums, res);
            nums.pop_back();
        }
    }
    
public:
    vector<vector<int>> combinationSum3(int k, int n) {
        vector<vector<int>> res;
        dfs(k, n, 1, 0, vector<int>(), res);
        return res;
    }
};
