class Solution {
public:
    void rotate(vector<vector<int>>& matrix) {
        int k = (matrix.size() + 1) >> 1, n = matrix.size() - 1, tmp;
        for (int i = 0; i < k; ++i) {
            for (int j = i; j < n - i; ++j) {
                tmp = matrix[i][j];
                matrix[i][j] = matrix[n - j][i];
                matrix[n - j][i] = matrix[n - i][n - j];
                matrix[n - i][n - j] = matrix[j][n - i];
                matrix[j][n - i] = tmp;
            }
        }
    }
};
