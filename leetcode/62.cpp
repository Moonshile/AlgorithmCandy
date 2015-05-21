class Solution {
public:
    int uniquePaths(int m, int n) {
        if (m == 0 || n == 0) {
            return 0;
        }
        vector<int> cur(n, 1), next(n, 1), *cur_p = &cur, *next_p = &next;
        for (int i = 1; i < m; ++i) {
            for (int j = 1; j < n; ++j) {
                (*next_p)[j] = (*next_p)[j - 1] + (*cur_p)[j];
            }
            swap(cur_p, next_p);
        }
        return (*cur_p)[n - 1];
    }
};
