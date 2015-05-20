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
    
public:
    int totalNQueens(int n) {
        vector<vector<int>> kills;
        for (int i = 0; i < n; ++i) {
            vector<int> k(n, 0);
            kills.push_back(k);
        }
        vector<int> positions(n, -1);
        int res = 0, i = 0;
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
            ++res;
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
