class Solution {
public:
    bool isValidSudoku(vector<vector<char>>& board) {
        unordered_map<int, bool> m;
        int row, col, grid, v;
        for (int i = 0; i < 9; ++i) {
            for (int j = 0; j < 9; ++j) {
                if (board[i][j] != '.') {
                    v = board[i][j] - '0';
                    row = (i<<4) | v;
                    col = 0x100 | (j<<4) | v;
                    grid = 0x200 | ((i/3*3 + j/3)<<4) | v;
                    if (m.count(row) == 0 && m.count(col) == 0 && m.count(grid) == 0) {
                        m[row] = m[col] = m[grid] = true;
                    } else {
                        return false;
                    }
                }
            }
        }
        return true;
    }
};
