class Solution {
public:
    vector<vector<int>> combinationSum(vector<int>& candidates, int target) {
        sort(candidates.begin(), candidates.end());
        int level = 0, i = 0, cur = 0;
        vector<vector<int>> res;
        vector<int> c, level_base;
        while (level >= 0) {
            // forwarding
            for(; cur < target; ++level) {
                level_base.push_back(i);
                c.push_back(candidates[i]);
                cur += candidates[i];
            }
            // success
            if (cur == target) {
                vector<int> tmp = c;
                res.push_back(c);
            }
            // backwarding
            do {
                --level;
                if (level >= 0) {
                    i = level_base.back();
                    // locate to next different i to avoid duplicates
                    for (int old_i = i; i < candidates.size() && candidates[i] == candidates[old_i]; ++i) {}
                } else {
                    i = -1;
                }
                cur -= c.back();
                c.pop_back();
                level_base.pop_back();
            } while (level >= 0 && (i == candidates.size() || target - cur < candidates[i]));
        }
        return res;
    }
};
