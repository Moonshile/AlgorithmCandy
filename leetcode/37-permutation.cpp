
class Solution {
private:
    static inline int row(int i, int v) { return (i<<4) | v; }
    static inline int col(int j, int v) { return 0x100 | (j<<4) | v; }
    static inline int grid(int i, int j, int v) { return 0x200 | ((i/3*3 + j/3)<<4) | v; }
    static inline bool isBusyCell(int i, int j, int v, vector<bool> &m) { return m[row(i, v)] || m[col(j, v)] || m[grid(i, j, v)]; }
    static inline void setBusyCell(int i, int j, int v, vector<bool> &m) { m[row(i, v)] = m[col(j, v)] = m[grid(i, j, v)] = true; }
    static inline void resetBusyCell(int i, int j, int v, vector<bool> &m) { m[row(i, v)] = m[col(j, v)] = m[grid(i, j, v)] = false; }
    
    friend struct EmptyCell;
    struct EmptyCell {
        vector<int> positions;
        vector<int> space;
        
        EmptyCell(vector<int> p, vector<int> s): positions(p), space(s) {}

        bool next_permutation_nlt(vector<int> &v, int offset) {
            for (auto i = v.begin() + offset + 1; i != v.end(); ++i) {
                if (*i > v[offset]) {
                    iter_swap(v.begin() + offset, i);
                    sort(v.begin() + offset + 1, v.end());
                    return !is_sorted(v.begin(), v.end());
                }
            }
            return next_permutation(v.begin(), v.end());
        }
        
        bool forward(int i, vector<bool> &m) {
            int k;
            do {
                for (k = 0; k < space.size(); ++k) {
                    int j = positions[k], v = space[k];
                    if (Solution::isBusyCell(i, j, v, m)) {
                        break;
                    } else {
                        Solution::setBusyCell(i, j, v, m);
                    }
                }
                if (k == space.size()) {
                    return true;
                }
                for (int w = 0; w < k; ++w) {
                    int j = positions[w], v = space[w];
                    Solution::resetBusyCell(i, j, v, m);
                }
            } while (next_permutation_nlt(space, k));
            return false;
        }
    };
    
    // return false if there is a row contains only one empty cell and the only value is invalid
    bool install(vector<vector<char>> &board, vector<bool> &m, vector<EmptyCell> &map) {
        for (int i = 0; i < 9; ++i) {
            vector<int> positions, space;
            for (int j = 0; j < 9; ++j) {
                board[i][j] != '.' ? setBusyCell(i, j, board[i][j] - '0', m) : positions.push_back(j);
            }
            for (int v = 1; v <= 9; ++v) {
                if (!m[row(i, v)]) {
                    space.push_back(v);
                }
            }
            // if there is only one empty cell in the row, then try to fill it with the only value
            if (space.size() == 1) {
                int j = positions[0], v = space[0];
                if (isBusyCell(i, j, v, m)) {
                    return false;
                }
                setBusyCell(i, j, v, m);
                positions.clear();
                space.clear();
            }
            EmptyCell ec(positions, space);
            map.push_back(ec);
        }
        return true;
    }
    
public:
    void solveSudoku(vector<vector<char>>& board) {
        vector<bool> m(0x300, false);
        vector<EmptyCell> map;
        install(board, m, map);
        int i = 0;
        while (i >= 0) {
            // forwarding
            for(; i < 9; ++i) {
                if (map[i].space.size() > 0 && !map[i].forward(i, m)) {
                    break;
                }
            }
            // success
            if (i == 9) {
                for (int ii = 0; ii < 9; ++ii) {
                    for (int k = 0; k < map[ii].space.size(); ++k) {
                        int j = map[ii].positions[k], v = map[ii].space[k] + '0';
                        board[ii][j] = v;
                    }
                }
                return;
            }
            // backwarding
            for (--i; i >= 0; --i) {
                for (int k = 0; k < map[i].space.size(); ++k) {
                    int j = map[i].positions[k], v = map[i].space[k];
                    resetBusyCell(i, j, v, m);
                }
                if (next_permutation(map[i].space.begin(), map[i].space.end())) {
                    break;
                }
            }
        }
    }
};
