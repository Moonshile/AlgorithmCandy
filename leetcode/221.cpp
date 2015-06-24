class Solution {
private:
    int largestSquareArea(vector<int> &height) {
        stack<int> ascend;
        int res = 0, i = 0;
        height.push_back(0);
        while (i < height.size()) {
            if (ascend.empty() || height[ascend.top()] <= height[i]) {
                ascend.push(i++);
            } else {
                int j = ascend.top();
                ascend.pop();
                int edge = min(height[j], (ascend.empty() ? i : i - ascend.top() - 1));
                res = max(res, edge*edge);
            }
        }
        height.pop_back();
        return res;
    }
    
public:
    int maximalSquare(vector<vector<char>> &matrix) {
        vector<int> histogram(matrix.size() > 0 ? matrix[0].size() : 0, 0);
        int res = 0;
        for (auto &row: matrix) {
            for (int j = 0; j < row.size(); ++j) {
                histogram[j] = row[j] == '0' ? 0 : histogram[j] + 1;
            }
            res = max(res, largestSquareArea(histogram));
        }
        return res;
    }
};
