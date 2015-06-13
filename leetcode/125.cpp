class Solution {
private:
    inline bool isAlpha(char c) { return c >= 'a' && c <= 'z' || c >= 'A' && c <= 'Z' || c >= '0' && c <= '9'; }
    inline char toLower(char c) { return c >= 'a' && c <= 'z' ? c : (c >= 'A' && c <= 'Z' ? c - 'A' + 'a' : c); }
    inline bool equalIgnoreCase(char c1, char c2) { return toLower(c1) == toLower(c2); }
    
public:
    bool isPalindrome(string s) {
        int n = s.size();
        for (int i = 0, j = n - 1; i < j; ++i, --j) {
            for (; i < n && !isAlpha(s[i]); ++i) {}
            for (; j >= 0 && !isAlpha(s[j]); --j) {}
            if (i < j && !equalIgnoreCase(s[i], s[j])) {
                return false;
            }
        }
        return true;
    }
};
