// compute from right bottom to left top
class Solution {
public:
    int calculateMinimumHP(vector<vector<int>>& dungeon) {
        int m = dungeon.size(), n = m > 0 ? dungeon[0].size() : 0;
        vector<int> cur(n + 1, INT_MAX), next(n + 1, INT_MAX), *cur_p = &cur, *next_p = &next;
        if (n > 0) {
            cur[n - 1] = 1;
        }
        for (int i = m - 1; i >= 0; --i) {
            for (int j = n - 1; j >= 0; --j) {
                (*next_p)[j] = max(min((*cur_p)[j], (*next_p)[j + 1]) - dungeon[i][j], 1);
            }
            swap(cur_p, next_p);
        }
        return (*cur_p)[0];
    }
};
