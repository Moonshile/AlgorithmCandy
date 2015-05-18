class Solution {
public:
    int longestValidParentheses(string s) {
        vector<bool> subs(s.size(), false);
        stack<int> pos;
        for (int i = 0; i < s.size(); ++i) {
            if (s[i] == '(') {
                pos.push(i);
            } else if (!pos.empty()) {
                subs[i] = subs[pos.top()] = true;
                pos.pop();
            }
        }
        int res = 0, cur = 0;
        for (auto i: subs) {
            if (i) {
                ++cur;
            } else if (cur > 0) {
                res = res > cur ? res : cur;
                cur = 0;
            }
        }
        return res > cur ? res : cur;
    }
};
