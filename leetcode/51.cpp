class Solution {
private:
    void killDo(vector<vector<int>> &kills, int i, int j, int k) {
        for (int m = 0; m < kills.size(); ++m) {
            kills[i][m] += k;
            kills[m][j] += k;
            if (i + m < kills.size() && j + m < kills.size()) {
                kills[i + m][j + m] += k;
            }
            if (i - m >= 0 && j - m >= 0) {
                kills[i - m][j - m] += k;
            }
            if (i + m < kills.size() && j - m >= 0) {
                kills[i + m][j - m] += k;
            }
            if (i - m >= 0 && j + m < kills.size()) {
                kills[i - m][j + m] += k;
            }
        }
    }
    
    void kill(vector<vector<int>> &kills, int i, int j) {
        killDo(kills, i, j, 1);
    }
    
    void unkill(vector<vector<int>> &kills, int i, int j) {
        killDo(kills, i, j, -1);
    }
    
    vector<string> getPuzzle(vector<int> &positions) {
        vector<string> res;
        for (int i = 0; i < positions.size(); ++i) {
            string p(positions.size(), '.');
            p[positions[i]] = 'Q';
            res.push_back(p);
        }
        return res;
    }
    
public:
    vector<vector<string>> solveNQueens(int n) {
        vector<vector<int>> kills;
        for (int i = 0; i < n; ++i) {
            vector<int> k(n, 0);
            kills.push_back(k);
        }
        vector<int> positions(n, -1);
        vector<vector<string>> res;
        int i = 0;
        while (i >= 0) {
            // forwarding
            for(; i < n; ++i) {
                int j = positions[i] + 1;
                for (; kills[i][j] > 0 && j < n; ++j) {}
                if (j == n) {
                    positions[i] = -1;
                    goto backwarding;
                }
                kill(kills, i, j);
                positions[i] = j;
            }
            // success
            res.push_back(getPuzzle(positions));
            // backwarding
        backwarding:
            --i;
            if (i >= 0) {
                unkill(kills, i, positions[i]);
            }
        }
        return res;
    }
};
