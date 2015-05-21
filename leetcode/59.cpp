class Solution {
private:
    vector<vector<int>> generateMatrixDo(int m, int n) {
        vector<vector<int>> res;
        for (int i = 0; i < m; ++i) {
            vector<int> tmp(n, 0);
            res.push_back(tmp);
        }
        int ki = (m + 1)>>1, kj = (n + 1)>>1, mm = m - 1, nn = n - 1, num = 1;
        for (int i = 0, j = 0; i < ki && j < kj; ++i, ++j) {
            for (int jj = j; jj < nn - j; ++jj) {
                res[i][jj] = num++;
            }
            for (int ii = i; ii < mm - i; ++ii) {
                res[ii][nn - j] = num++;
            }
            if (i != mm - i) {
                for (int jj = nn - j; jj > j; --jj) {
                    res[mm - i][jj] = num++;
                }
            }
            if (j != nn - j) {
                for (int ii = mm - i; ii > i; --ii) {
                    res[ii][j] = num++;
                }
            }
            if (i == mm - i || j == nn - j) {
                res[mm - i][nn - j] = num++;
            }
        }
        return res;
    }
    
public:
    vector<vector<int>> generateMatrix(int n) {
        return generateMatrixDo(n, n);
    }
};
