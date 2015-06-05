/*
 * This solution is a variant of backtracking.
 * It tries to generate a xor sequence, e.g.
 * For n = 1: [1]
 * For n = 2: [1,2,1]
 * For n = 3: [1,2,1,4,1,2,1]
 * For n = 4: [1,2,1,4,1,2,1,8,1,2,1,4,1,2,1]
 */

class Solution {
public:
    vector<int> grayCode(int n) {
        vector<int> res{0};
        vector<int> x;
        for (int i = 0, m = 1; i < n; ++i, m <<= 1) {
            x.push_back(m);
            for (int j = 0, n = x.size() - 1; j < n; ++j) {
                x.push_back(x[j]);
            }
        }
        for (int i = 0; i < x.size(); ++i) {
            res.push_back(res.back()^x[i]);
        }
        return res;
    }
};
