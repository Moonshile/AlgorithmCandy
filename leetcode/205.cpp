class Solution {
private:
    string normalize(const string &s) {
        unordered_map<char, char> m;
        char c = 'a';
        stringstream ss;
        for (int i = 0; i < s.size(); ++i) {
            if (m.count(s[i]) == 0) {
                m[s[i]] = c++;
            }
            ss << m[s[i]];
        }
        return ss.str();
    }
    
public:
    bool isIsomorphic(string s, string t) {
        return normalize(s) == normalize(t);
    }
};
