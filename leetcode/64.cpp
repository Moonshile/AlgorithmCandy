class Solution {
public:
    int minPathSum(vector<vector<int>>& grid) {
        if (grid.size() == 0 || grid[0].size() == 0) {
            return 0;
        }
        int m = grid.size(), n = grid[0].size();
        vector<int> cur(n, 0), next(n, 0), *cur_p = &cur, *next_p = &next;
        for (int i = 0; i < n; ++i) {
            cur[i] = i == 0 ? grid[0][i] : cur[i - 1] + grid[0][i];
        }
        for (int i = 1; i < m; ++i) {
            for (int j = 0; j < n; ++j) {
                (*next_p)[j] = j == 0 ? (*cur_p)[j] + grid[i][j] : min((*cur_p)[j], (*next_p)[j - 1]) + grid[i][j];
            }
            swap(cur_p, next_p);
        }
        return (*cur_p)[n - 1];
    }
};
