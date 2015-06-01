class Solution {
private:
    vector<int> buildNext(string &needle) {
        vector<int> next(needle.size(), -1);
        int m = needle.size(), i = 0, j = -1;
        while (i < m - 1) {
            if (j < 0 || needle[i] == needle[j]) {
                ++i;
                ++j;
                next[i] = needle[i] == needle[j] ? next[j] : j;
            } else {
                j = next[j];
            }
        }
        return next;
    }
    
    int match(string &haystack, string &needle) {
        vector<int> next = buildNext(needle);
        int m = haystack.size(), n = needle.size(), i = 0, j = 0;
        while (i < m && j < n) {
            if (j < 0 || haystack[i] == needle[j]) {
                ++i;
                ++j;
            } else {
                j = next[j];
            }
        }
        return j == n ? i - j : -1;
    }
    
public:
    int strStr(string haystack, string needle) {
        return match(haystack, needle);
    }
};
