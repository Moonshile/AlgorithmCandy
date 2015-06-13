// O(n^2)
class Solution {
public:
    vector<int> getRow(int rowIndex) {
        vector<int> res(rowIndex + 1, 0);
        for (int i = rowIndex; i >= 0; --i) {
            res[i] = 1;
            for (int j = i + 1; j <= rowIndex; ++j) {
                res[j] = j == rowIndex ? 1 : res[j] + res[j + 1];
            }
        }
        return res;
    }
};
