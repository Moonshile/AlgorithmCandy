class Solution {
public:
    vector<int> grayCode(int n) {
        vector<int> res{0};
        int x = 1;
        for (int i = 0; i < n; ++i) {
            for (int j = res.size() - 1; j >= 0; --j) {
                res.push_back(res[j]^x);
            }
            x <<= 1;
        }
        return res;
    }
};
