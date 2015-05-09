class Solution {
public:
    bool isValid(string s) {
        stack<char> lefts;
        for (auto c: s) {
            if (c == '(' || c == '[' || c == '{') {
                lefts.push(c == '(' ? ')' : (c == '[' ? ']' : '}'));
            } else if (!lefts.empty() && c == lefts.top()) {
                lefts.pop();
            } else {
                return false;
            }
        }
        return lefts.empty();
    }
};