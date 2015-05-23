class Solution {
public:
    vector<vector<int>> combine(int n, int k) {
        vector<vector<int>> res;
        vector<int> cur, tmp;
        int i = 0;
        for (; i < k; ++i) {
            cur.push_back(i + 1);
        }
        while (i > 0) {
            // forwarding
            for (; i < k; ++i) {
                if (cur[i - 1] == n) {
                    goto backwarding;
                }
                cur[i] = cur[i - 1] + 1;
            }
            // success
            tmp = cur;
            res.push_back(tmp);
            // backwarding:
        backwarding:
            for (; cur[i - 1] == n; --i) {}
            if (i > 0) {
                ++cur[i - 1];
            }
        }
        return res;
    }
};
