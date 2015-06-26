class Solution {
public:
    bool wordBreak(string s, unordered_set<string>& wordDict) {
        vector<bool> in_dict(s.size() + 1, false);
        in_dict[0] = true;
        for (int i = 1, n = s.size(); i <= n; ++i) {
            for (int j = 0; j < i; ++j) {
                if (in_dict[j] && wordDict.count(s.substr(j, i - j)) > 0) {
                    in_dict[i] = true;
                    break;
                }
            }
        }
        return in_dict.back();
    }
};
