class Solution {
private:
    bool canBreak(string &s, unordered_set<string>& wordDict) {
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
    
    void dfs(string &s, int last, int min_len, int max_len, vector<string> &res, unordered_set<string>& wordDict) {
        if (last < 0) {
            res.push_back("");
            return;
        }
        for (int i = last - min_len + 1; i >= 0 && last - i + 1 <= max_len; --i) {
            string tmp = s.substr(i, last - i + 1);
            if (wordDict.count(tmp) > 0) {
                vector<string> parts;
                dfs(s, i - 1, min_len, max_len, parts, wordDict);
                for (auto &part: parts) {
                    part = part + (part.empty() ? "" : " ") + tmp;
                    res.push_back(part);
                }
            }
        }
    }
    
public:
    vector<string> wordBreak(string s, unordered_set<string>& wordDict) {
        int min_len = INT_MAX, max_len = INT_MIN;
        for (auto &w: wordDict) {
            min_len = min(min_len, static_cast<int>(w.size()));
            max_len = max(max_len, static_cast<int>(w.size()));
        }
        vector<string> res;
        if (canBreak(s, wordDict)) {
            dfs(s, s.size() - 1, min_len, max_len, res, wordDict);
        }
        return res;
    }
};
