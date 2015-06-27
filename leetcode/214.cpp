class Solution {
private:
    vector<int> buildNext(string &needle) {
        vector<int> next(needle.size(), -1);
        int m = needle.size(), i = 0, j = -1;
        while (i < m - 1) {
            if (j < 0 || needle[i] == needle[j]) {
                ++i;
                ++j;
                next[i] = j;
            } else {
                j = next[j];
            }
        }
        return next;
    }
    
public:
    string shortestPalindrome(string s) {
        string tmp = s;
        reverse(tmp.begin(), tmp.end());
        string long_pal = s + "#" + tmp;
        auto next = buildNext(long_pal);
        return tmp.substr(0, s.size() - next.back() - 1) + s;
    }
};
