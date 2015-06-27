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

public:
    int minCut(string s) {
        vector<int> res(s.size() + 1, -1);
        auto palindrome_map = getPalindromeMap(s);
        for (int i = s.size() - 1; i >= 0; --i) {
            res[i] = s.size() - 1;
            for (int j = i; j < s.size(); ++j) {
                if (palindrome_map[i][j]) {
                    res[i] = min(res[i], res[j + 1] + 1);
                }
            }
        }
        return res[0];
    }
};
