class Solution {
public:
    int longestValidParentheses(string s) {
        stack<int> pos;
        int res = 0, very_left = -1;
        for (int i = 0; i < s.size(); ++i) {
            if (s[i] == '(') {
                pos.push(i);
            } else if (!pos.empty()) {
                pos.pop();
            } else {
                very_left = i;
            }
            res = max(res, i - (pos.empty() ? very_left : pos.top()));
        }
        return res;
    }
};
