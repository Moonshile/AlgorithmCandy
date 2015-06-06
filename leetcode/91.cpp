// In fact, I think when s is empty, the result should be 1, 
// because it need not to be decoded, which means that in fact
// there exists a way to decode an empty string.
class Solution {
public:
    int numDecodings(string s) {
        int pre_pre = 1, pre, cur = 0;
        for (int i = 0; i < s.size(); ++i) {
            if (i == 0) {
                cur = pre = s[i] == '0' ? 0 : 1;
            } else {
                cur = s[i] == '0' ? 0 : pre;
                cur += s[i - 1] == '1' || s[i - 1] == '2' && s[i] >= '0' && s[i] <= '6' ? pre_pre : 0;
                pre_pre = pre;
                pre = cur;
            }
        }
        return cur;
    }
};
