class Solution {
public:
    vector<vector<int>> generateMatrix(int n) {
        vector<vector<int>> res;
        for (int i = 0; i < n; ++i) {
            vector<int> tmp(n, 0);
            res.push_back(tmp);
        }
        int k = (n + 1)>>1, num = 1;
        for (int i = 0, j = 0; i < k && j < k; ++i, ++j) {
            for (int jj = j; jj < n - 1 - j; ++jj) {
                res[i][jj] = num++;
            }
            for (int ii = i; ii < n - 1 - i; ++ii) {
                res[ii][n - 1 - j] = num++;
            }
            if (i != n - 1 - i) {
                for (int jj = n - 1 - j; jj > j; --jj) {
                    res[n - 1 - i][jj] = num++;
                }
            }
            if (j != n - 1 - j) {
                for (int ii = n - 1 - i; ii > i; --ii) {
                    res[ii][j] = num++;
                }
            }
            if (i == n - 1 - i || j == n - 1 - j) {
                res[n - 1 - i][n - 1 - j] = num++;
            }
        }
        return res;
    }
};
