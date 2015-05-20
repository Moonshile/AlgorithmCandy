class Solution {
public:
    vector<int> spiralOrder(vector<vector<int>>& matrix) {
        vector<int> res;
        if (matrix.size() == 0 || matrix[0].size() == 0) {
            return res;
        }
        int ik = (matrix.size() + 1)>>1, m = matrix.size() - 1, jk = (matrix[0].size() + 1)>>1, n = matrix[0].size() - 1;
        for (int i = 0, j = 0; i < ik && j < jk; ++i, ++j) {
            for (int jj = j; jj < n - j; ++jj) {
                res.push_back(matrix[i][jj]);
            }
            for (int ii = i; ii < m - i; ++ii) {
                res.push_back(matrix[ii][n - j]);
            }
            if (i != m - i) {
                for (int jj = n - j; jj > j; --jj) {
                    res.push_back(matrix[m - i][jj]);
                }
            }
            if (j != n - j) {
                for (int ii = m - i; ii > i; --ii) {
                    res.push_back(matrix[ii][j]);
                }
            }
            if (i == m - i || j == n - j) {
                res.push_back(i == m - i ? matrix[i][n - j] : matrix[m - i][j]);
            }
        }
        return res;
    }
};
