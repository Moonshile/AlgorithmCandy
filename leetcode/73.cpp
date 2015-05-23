class Solution {
public:
    void setZeroes(vector<vector<int>>& matrix) {
        bool pre_has_zero = false;
        for (int i = 0; i < matrix.size(); ++i) {
            for (int j = 0; j < matrix[i].size(); ++j) {
                if (matrix[i][j] == 0) {
                    for (int k = 0; k < j; ++k) {
                        matrix[i][k] = matrix[i][k] == 0 && i != matrix.size() - 1 ? -1 : 0;
                    }
                    for (int k = j; k < matrix[i].size(); ++k) {
                        if (matrix[i][k] == 0) {
                            for (int w = 0; w < i; ++w) {
                                matrix[w][k] = 0;
                            }
                            matrix[i][k] = i == matrix.size() - 1 ? 0 : -1;
                        } else if (pre_has_zero && matrix[i - 1][k] == -1) {
                            matrix[i - 1][k] = 0;
                            matrix[i][k] = i == matrix.size() - 1 ? 0 : -1;
                        } else if (!pre_has_zero && i > 0 && i != matrix.size() - 1 && matrix[i - 1][k] == 0) {
                            matrix[i][k] = -1;
                        } else {
                            matrix[i][k] = 0;
                        }
                    }
                    pre_has_zero = true;
                    break;
                } else if (i > 0 && pre_has_zero && matrix[i - 1][j] == -1) {
                    matrix[i - 1][j] = 0;
                    matrix[i][j] = 0;
                } else if (i > 0 && !pre_has_zero && matrix[i - 1][j] == 0) {
                    matrix[i][j] = 0;
                }
                if (j == matrix[i].size() - 1) {
                    pre_has_zero = false;
                }
            }
        }
    }
};
