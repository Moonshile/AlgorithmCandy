class Solution {
private:
    bool strcmp(string::const_iterator s1, string::const_iterator s1_end, string::const_iterator s2, string::const_iterator s2_end) {
        for(; s1 != s1_end && s2 != s2_end; ++s1, ++s2) {
            if (*s1 != *s2) {
                break;
            }
        }
        return s2 == s2_end;
    }
public:
    int strStr(string haystack, string needle) {
        if (haystack.size() < needle.size()) {
            return -1;
        }
        for (auto i = haystack.begin(); i != haystack.end() - needle.size() + 1; ++i) {
            if (strcmp(i, i + needle.size(), needle.begin(), needle.end())) {
                return i - haystack.begin();
            }
        }
        return -1;
    }
};
