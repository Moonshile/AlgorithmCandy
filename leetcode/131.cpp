class Solution {
private:
    vector<vector<bool>> getPalindromeMap(string &s) {
        vector<vector<bool>> res(s.size(), vector<bool>(s.size(), false));
        for (int i = s.size() - 1; i >= 0; --i) {
            for (int j = i; j < s.size(); ++j) {
                if (s[i] == s[j] && (j - i < 2 || res[i + 1][j - 1])) {
                    res[i][j] = true;
                }
            }
        }
        return res;
    }
    
    void dfs(string &s, int last, vector<vector<string>> &res, vector<vector<bool>> &palMap) {
        if (last == -1) {
            res.push_back(vector<string>());
            return;
        }
        for (int i = last; i >= 0; --i) {
            if (palMap[i][last]) {
                vector<vector<string>> parts;
                dfs(s, i - 1, parts, palMap);
                for (auto &part: parts) {
                    part.push_back(s.substr(i, last - i + 1));
                    res.push_back(part);
                }
            }
        }
    }
    
public:
    vector<vector<string>> partition(string s) {
        vector<vector<string>> res;
        auto palMap = getPalindromeMap(s);
        dfs(s, s.size() - 1, res, palMap);
        return res;
    }
};
