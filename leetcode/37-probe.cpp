class Solution {
private:
    static inline int row(int i, int v) { return (i<<4) | v; }
    static inline int col(int j, int v) { return 0x100 | (j<<4) | v; }
    static inline int grid(int i, int j, int v) { return 0x200 | ((i/3*3 + j/3)<<4) | v; }
    static inline bool isBusyCell(int i, int j, int v, vector<bool> &m) { return m[row(i, v)] || m[col(j, v)] || m[grid(i, j, v)]; }
    static inline void setBusyCell(int i, int j, int v, vector<bool> &m) { m[row(i, v)] = m[col(j, v)] = m[grid(i, j, v)] = true; }
    static inline void resetBusyCell(int i, int j, int v, vector<bool> &m) { m[row(i, v)] = m[col(j, v)] = m[grid(i, j, v)] = false; }
    
    struct EmptyCell {
        int index;
        int size;
        vector<int> positions;
        EmptyCell(vector<int> &p): index(0), size(p.size()), positions(p) {}
    };
    
    // return false if there is a row contains only one empty cell and the only value is invalid
    void install(vector<vector<char>> &board, vector<bool> &m, vector<EmptyCell> &map) {
        for (int i = 0; i < 9; ++i) {
            vector<int> positions;
            for (int j = 0; j < 9; ++j) {
                board[i][j] != '.' ? setBusyCell(i, j, board[i][j] - '0', m) : positions.push_back(j);
            }
            map.push_back(positions);
        }
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
                for (; map[i].index < map[i].size; ++map[i].index) {
                    int j = map[i].positions[map[i].index], cv = board[i][j], v;
                    if (cv != '.') {
                        board[i][j] = '.';
                        resetBusyCell(i, j, cv - '0', m);
                    }
                    for (v = cv == '.' ? 1 : cv - '0' + 1; v <= 9 && isBusyCell(i, j, v, m); ++v) {}
                    if (v > 9) {
                        goto backwarding;
                    } else {
                        setBusyCell(i, j, v, m);
                        board[i][j] = v + '0';
                    }
                }
            }
            // success
            return;
            // backwarding
        backwarding:
            if (map[i].index == 0) {
                --i;
            }
            --map[i].index;
        }
    }
};
