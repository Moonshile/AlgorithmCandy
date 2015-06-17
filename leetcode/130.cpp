class Solution {
private:
    static constexpr char OUTER_O() { return '0'; }

    void nextO(vector<vector<char>> &board, queue<pair<int, int>> &q, int i, int j, int m, int n) {
        if (i >= 0 && i < m && j >= 0 && j < n && board[i][j] == 'O') {
            board[i][j] = OUTER_O();
            q.push(pair<int, int>(i, j));
        }
    }
    
    void replaceOuter(vector<vector<char>> &board, int i, int j, int m, int n) {
        if (board[i][j] == 'O') {
            board[i][j] = OUTER_O();
            queue<pair<int, int>> q({pair<int, int>(i, j)});
            while (!q.empty()) {
                auto p = q.front();
                q.pop();
                int ii = p.first, jj = p.second;
                nextO(board, q, ii - 1, jj, m, n);
                nextO(board, q, ii + 1, jj, m, n);
                nextO(board, q, ii, jj - 1, m, n);
                nextO(board, q, ii, jj + 1, m, n);
            }
        }
    }
public:
    void solve(vector<vector<char>> &board) {
        int m = board.size(), n = m > 0 ? board[0].size() : 0;
        for (int i = 0, j = 0; i < m && j < n; ++i) {
            replaceOuter(board, i, j, m, n);
        }
        for (int i = 0, j = n - 1; i < m && j >= 0; ++i) {
            replaceOuter(board, i, j, m, n);
        }
        for (int i = 0, j = 0; i < m && j < n; ++j) {
            replaceOuter(board, i, j, m, n);
        }
        for (int i = m - 1, j = 0; i >= 0 && j < n; ++j) {
            replaceOuter(board, i, j, m, n);
        }
        for (auto &line: board) {
            for (auto &c: line) {
                c = c == OUTER_O() ? 'O' : 'X';
            }
        }
    }
};
