class Solution {
public:
    int numDistinct(string s, string t) {
        int m = s.size(), n = t.size() + 1;
        vector<int> cur(n, 0), next = cur, *cur_p = &cur, *next_p = &next;
        cur[0] = 1;
        for (int i = 0; i < m; ++i) {
            for (int j = 0; j < n; ++j) {
                (*next_p)[j] = j == 0 ? 1 : (*cur_p)[j] + (s[i] == t[j - 1] ? (*cur_p)[j - 1] : 0);
            }
            swap(cur_p, next_p);
        }
        return (*cur_p)[n - 1];
    }
};
