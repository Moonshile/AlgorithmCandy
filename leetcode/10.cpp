class Solution {
    bool match(const char *s, const char *p) {
        if ( *p == '\0') {
            return *s == '\0';
        }
        if (p[1] == '\0' || p[1] != '*') {
            if (s[0] && (s[0] == p[0] || p[0] == '.')) {
                return match(s + 1, p + 1);
            } else {
                return false;
            }
        } else {
            while (*s && (p[0] == '.' || s[0] == p[0])) {
                if (match(s, p + 2)) {
                    return true;
                }
                ++s;
            }
            return match(s, p + 2);
        }
    }
public:
    bool isMatch(string s, string p) {
        return match(s.c_str(), p.c_str());
    }
};