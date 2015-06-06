class Solution {
public:
    int numTrees(int n) {
        vector<int> res{1, 1};
        for (int i = 2; i <= n; ++i) {
            int tmp = 0;
            for (int j = 0; j < (i + 1)>>1; ++j) {
                int t = res[j]*res[i - 1 - j];
                tmp += j == i - 1 - j ? t : t<<1;
            }
            res.push_back(tmp);
        }
        return res[n];
    }
};
