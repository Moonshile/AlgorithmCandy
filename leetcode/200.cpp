class Solution {
private:
    static constexpr char accessed() { return '.'; }
    static constexpr char island() { return '1'; }
    
    inline void set(vector<vector<char>> &grid, int i, int j, int m, int n) {
        if (i >= 0 && i < m && j >= 0 && j < n && grid[i][j] == island()) {
            grid[i][j] = accessed();
        }
    }
    
    inline void setAndPush(vector<vector<char>> &grid, int i, int j, int m, int n, queue<pair<int, int>> &q) {
        if (i >= 0 && i < m && j >= 0 && j < n && grid[i][j] == island()) {
            set(grid, i, j, m, n);
            q.push(pair<int, int>(i, j));
        }
    }
    
    void bfs(vector<vector<char>> &grid, int i, int j, int m, int n) {
        queue<pair<int, int>> q;
        setAndPush(grid, i, j, m, n, q);
        while (!q.empty()) {
            auto p = q.front();
            q.pop();
            int ii = p.first, jj = p.second;
            setAndPush(grid, ii - 1, jj, m, n, q);
            setAndPush(grid, ii + 1, jj, m, n, q);
            setAndPush(grid, ii, jj - 1, m, n, q);
            setAndPush(grid, ii, jj + 1, m, n, q);
        }
    }
    
public:
    int numIslands(vector<vector<char>>& grid) {
        int res = 0;
        for (int i = 0, m = grid.size(); i < m; ++i) {
            for (int j = 0, n = grid[i].size(); j < n; ++j) {
                if (grid[i][j] == island()) {
                    ++res;
                    bfs(grid, i, j, m, n);
                }
            }
        }
        for (int i = 0, m = grid.size(); i < m; ++i) {
            for (int j = 0, n = grid[i].size(); j < n; ++j) {
                if (grid[i][j] == accessed()) {
                    grid[i][j] = island();
                }
            }
        }
        return res;
    }
};
