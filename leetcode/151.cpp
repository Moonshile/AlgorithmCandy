class Solution {
public:
    void reverseWords(string &s) {
        reverse(s.begin(), s.end());
        auto i = s.begin(), j = s.begin();
        while (j != s.end() && *j == ' ') {
            ++j;
        }
        while (j != s.end()) {
            auto old_i = i;
            while (j != s.end() && *j != ' ') {
                *i++ = *j++;
            }
            while (j != s.end() && *j == ' ') {
                ++j;
            }
            reverse(old_i, i);
            if (j != s.end()) {
                *i++ = ' ';
            }
        }
        s.erase(i, s.end());
    }
};
