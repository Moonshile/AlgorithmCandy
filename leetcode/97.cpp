class Solution {
public:
    bool isInterleave(string s1, string s2, string s3) {
        if (s1.size() + s2.size() != s3.size()) {
            return false;
        }
        int m = s1.size() + 1, n = s2.size() + 1;
        vector<bool> cur(n), pre(n), *cur_p = &cur, *pre_p = &pre;
        for (int i = 0; i < m; ++i) {
            for (int j = 0; j < n; ++j) {
                (*cur_p)[j] = j > 0 && (*cur_p)[j - 1] && s2[j - 1] == s3[i + j - 1] ||
                    i > 0 && (*pre_p)[j] && s1[i - 1] == s3[i + j - 1] ||
                    i == 0 && j == 0;
            }
            pre_p = cur_p;
        }
        return (*cur_p)[n - 1];
    }
};
