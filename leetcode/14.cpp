class Solution {
public:
    string longestCommonPrefix(vector<string>& strs) {
        string s;
        int len = 0;
        while (!strs.empty() && !strs[0].empty()) {
            string tmp = strs[0];
            for (auto s: strs) {
                if(s[len] != tmp[len]) {
                    goto result;
                }
            }
            ++len;
            continue;
        result:
            s = tmp.substr(0, len);
            break;
        }
        return s;
    }
};