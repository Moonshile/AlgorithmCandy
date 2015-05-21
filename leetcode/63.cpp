class Solution {
public:
    int uniquePathsWithObstacles(vector<vector<int>>& obstacleGrid) {
        int res = 0;
        for (int i = 0; i < obstacleGrid.size(); ++i) {
            for (int j = 0; j < obstacleGrid[i].size(); ++j) {
                if (obstacleGrid[i][j] == 1) {
                    obstacleGrid[i][j] = -1;
                } else if (i == 0 && j == 0) {
                    obstacleGrid[i][j] = 1;
                } else if (i == 0) {
                    obstacleGrid[i][j] = obstacleGrid[i][j - 1] == -1 ? 0 : obstacleGrid[i][j - 1];
                } else if (j == 0) {
                    obstacleGrid[i][j] = obstacleGrid[i - 1][j] == -1 ? 0 : obstacleGrid[i - 1][j];
                } else if (obstacleGrid[i - 1][j] == -1 && obstacleGrid[i][j - 1] == -1) {
                    obstacleGrid[i][j] = 0;
                } else if (obstacleGrid[i - 1][j] == -1) {
                    obstacleGrid[i][j] = obstacleGrid[i][j - 1];
                } else if (obstacleGrid[i][j - 1] == -1) {
                    obstacleGrid[i][j] = obstacleGrid[i - 1][j];
                } else {
                    obstacleGrid[i][j] = obstacleGrid[i][j - 1] + obstacleGrid[i - 1][j];
                }
                if (i == obstacleGrid.size() - 1 && j == obstacleGrid[i].size() - 1 && obstacleGrid[i][j] != -1) {
                    res = obstacleGrid[i][j];
                }
            }
        }
        return res;
    }
};
