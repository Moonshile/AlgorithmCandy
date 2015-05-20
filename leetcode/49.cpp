class Solution {
public:
    vector<string> anagrams(vector<string>& strs) {
        unordered_map<string, vector<string>> m;
        for(string &s: strs) {
            string key = s;
            sort(key.begin(), key.end());
            if (m.count(key) == 0) {
                vector<string> t;
                m[key] = t;
            }
            m[key].push_back(s);
        }
        vector<string> res;
        for (auto i: m) {
            if (i.second.size() > 1) {
                for (auto s: i.second) {
                    res.push_back(s);
                }
            }
        }
        return res;
    }
};
