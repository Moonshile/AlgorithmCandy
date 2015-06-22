class Solution {
private:
    static constexpr int mask() { return 0xFFFFF; }

    inline int encode(char c) {
        switch (c) {
            case 'A': return 0;
            case 'C': return 1;
            case 'G': return 2;
            case 'T':
            default: return 3;
        }
    }
    
public:
    vector<string> findRepeatedDnaSequences(string s) {
        vector<string> res;
        int cur = 0;
        for (int i = 0; i < 9 && i < s.size(); ++i) {
            cur = (cur << 2) | encode(s[i]);
        }
        unordered_map<int, int> occur;
        for (int i = 9; i < s.size(); ++i) {
            cur = (cur << 2) | encode(s[i]);
            int k = cur&mask();
            occur[k] = occur.count(k) > 0 ? occur[k] + 1 : 1;
            if (occur[k] == 2) {
                res.push_back(s.substr(i - 9, 10));
            }
        }
        return res;
    }
};
