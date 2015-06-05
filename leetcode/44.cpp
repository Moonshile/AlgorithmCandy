class Solution {
public:
    bool isMatch(string s, string p) {
        int solid = 0;
        for (char c: p) {
            solid += c == '*' ? 0 : 1;
        }
        if (solid > s.size()) {
            return false;
        }
        vector<bool> match(s.size() + 1, false);
        match[0] = true;
        for (char c: p) {
            if (c == '*') {
                for (int j = 1, m = s.size() + 1; j < m; ++j) {
                    match[j] = match[j - 1] || match[j];
                }
            } else {
                for (int j = s.size(); j > 0; --j) {
                    match[j] = match[j - 1] && (c == '?' || c == s[j - 1]);
                }
            }
            match[0] = match[0] && c == '*';
        }
        return match[s.size()];
    }
};
