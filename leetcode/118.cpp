class Solution {
public:
    vector<vector<int>> generate(int numRows) {
        vector<vector<int>> res;
        vector<int> cur;
        for (int i = 0; i < numRows; ++i) {
            vector<int> tmp{1};
            for (int j = 0, m = cur.size(); j < m; ++j) {
                tmp.push_back(j == m - 1 ? 1 : cur[j] + cur[j + 1]);
            }
            res.push_back(tmp);
            cur = tmp;
        }
        return res;
    }
};
