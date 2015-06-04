class Solution {
private:
    static const int ParentAtTop = 1, ParentAtRight = 2, ParentAtBottom = 3, ParentAtLeft = 4, Root = 5;
    static const int ChildAtTop = 0x10, ChildAtRight = 0x20, ChildAtBottom = 0x30, ChildAtLeft = 0x40, Leaf = 0x50;
    inline int getParent(int x) { return x&0xf; }
    inline int getChild(int x) { return x&0xf0; }
    
    static const vector<int> sequence;
    static const vector<int> parent_seq;
    static const vector<int> ii_delta;
    static const vector<int> jj_delta;
    
    bool searchChild(vector<vector<char>> &board, vector<vector<int>> &path, int &ii, int &jj, int m, int n, char target) {
        int parent = getParent(path[ii][jj]), child = getChild(path[ii][jj]), e;
        for (e = 0; e < sequence.size() && child != sequence[e]; ++e) {}
        for (; e < sequence.size(); ++e) {
            if (e > 0) {
                int i = ii + ii_delta[e - 1], j = jj + jj_delta[e - 1];
                if (i >= 0 && i < m && j >= 0 && j < n && getParent(path[i][j]) == parent_seq[e - 1]) {
                    path[i][j] = 0;
                }
            }
            if (e < sequence.size() - 1) {
                int i = ii + ii_delta[e], j = jj + jj_delta[e];
                if (i >= 0 && i < m && j >= 0 && j < n && path[i][j] == 0 && board[i][j] == target) {
                    path[ii][jj] = parent | sequence[e + 1];
                    path[i][j] = parent_seq[e] | Leaf;
                    ii = i;
                    jj = j;
                    return true;
                }
            }
        }
        return false;
    }
    
public:
    bool exist(vector<vector<char>>& board, string word) {
        if (word.empty()) {
            return true;
        }
        vector<vector<int>> path;
        for (int i = 0; i < board.size(); ++i) {
            vector<int> tmp(board[i].size(), 0);
            path.push_back(tmp);
        }
        for (int i = 0, m = board.size(); i < m; ++i) {
            for (int j = 0, n = board[i].size(); j < n; ++j) {
                if (board[i][j] != word[0]) {
                    continue;
                }
                path[i][j] = Root | Leaf;
                int w = 1, ii = i, jj = j;
                while (w > 0) {
                    // forwarding
                    while (w < word.size() && searchChild(board, path, ii, jj, m, n, word[w])) {
                        ++w;
                    }
                    // success
                    if (w == word.size()) {
                        return true;
                    }
                    // backwarding
                    --w;
                    switch (getParent(path[ii][jj])) {
                        case ParentAtTop: --ii; break;
                        case ParentAtRight: ++jj; break;
                        case ParentAtBottom: ++ii; break;
                        case ParentAtLeft: --jj; break;
                        case Root:
                        default: path[ii][jj] = 0; break;
                    }
                }
            }
        }
        return false;
    }
};

const vector<int> Solution::sequence{Leaf, ChildAtTop, ChildAtRight, ChildAtBottom, ChildAtLeft};
const vector<int> Solution::parent_seq{ParentAtBottom, ParentAtLeft, ParentAtTop, ParentAtRight};
const vector<int> Solution::ii_delta{-1, 0, 1, 0, 0xff};
const vector<int> Solution::jj_delta{0, 1, 0, -1, 0xff};
