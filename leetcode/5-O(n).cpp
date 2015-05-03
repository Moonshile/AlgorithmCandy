#include <iostream>
#include <string>
#include <vector>

using namespace std;

/*
 * Reference
 * 1. http://articles.leetcode.com/2011/11/longest-palindromic-substring-part-ii.html
 * 2. http://www.felix021.com/blog/read.php?2040
 */

class Solution {
private:

    const char start = '^';
    const char end = '$';
    const char default_interval = '#';

    string join(const string s, const char interval) const {
        string res("");
        res.append(1, start);
        res.append(1, interval);
        for (auto c: s) {
            res.append(1, c);
            res.append(1, interval);
        }
        res.append(1, end);
        return res;
    }

public:
    string longestPalindrome(string s) {
        string sInserted = join(s, default_interval);
        vector<unsigned int> p{1};
        unsigned int mx = 0, id = 0;
        for (unsigned int i = 1; i < sInserted.size(); ++i) {
            p.push_back(mx > i ? min(p[2*id - i], mx - i) : 1);
            while (sInserted[i + p[i]] == sInserted[i - p[i]]) {
                ++p[i];
            }
            if (i + p[i] > mx) {
                mx = i + p[i];
                id = i;
            }
        }
        unsigned int start = 0, len = 0;
        for (unsigned int i = 0; i < p.size(); ++i) {
            if (p[i] > len) {
                len = p[i] - 1;
                start = (i - p[i])/2;
            }
        }
        return s.substr(start, len);
    }
};

int main() {
    Solution s;
    vector<string> str = {"adam", "ccd", "aa", "abcb", "abababababa"};
    for (auto i: str) {
        cout << i << " " << s.longestPalindrome(i) << endl;
    }
    return 0;
}
