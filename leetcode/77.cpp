class Solution {
public:
    vector<vector<int>> combine(int n, int k) {
        vector<vector<int>> cur, next, *cur_p = &cur, *next_p = &next;
        for (int i = 1; i <= k; ++i) {
            if (i == 1) {
                for (int j = 1; j <= n; ++j) {
                    vector<int> tmp{j};
                    cur_p->push_back(tmp);
                }
            } else {
                next_p->clear();
                for (auto &pre: *cur_p) {
                    for (int j = pre[i - 2] + 1; j <= n; ++j) {
                        vector<int> tmp = pre;
                        tmp.push_back(j);
                        next_p->push_back(tmp);
                    }
                }
                swap(cur_p, next_p);
            }
        }
        return *cur_p;
    }
};
