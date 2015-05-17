class Solution {
private:
    void find(const string &s, const int base_index, const int len, const int size, unordered_map<string, int> &m, vector<int> &res) {
        int counts = s.size()/len*len, matched = 0, j = 0;
        for (int i = 0; i < counts; i += len) {
            string sub = s.substr(i, len);
            if(m.count(sub) == 0 || m[sub] == 0) {
                // if i is not in m, or i is already used up, then failed
                for (; j < i; j += len) {
                    string jsub = s.substr(j, len);
                    if (m.count(jsub)) {
                        ++m[jsub];
                        --matched;
                    }
                    // if i is used up and meet another earlier jsub which equals to i
                    if (m.count(sub) && m[sub]) {
                        --m[jsub];
                        ++matched;
                        j +=len;
                        break;
                    }
                }
            } else {
                // if i is in m and hasn't been used up yet
                matched == 0 ? j = i : j;
                --m[sub];
                ++matched;
                if (matched == size) {
                    res.push_back(j + base_index);
                    ++m[s.substr(j, len)];
                    --matched;
                    j += len;
                }
            }
        }
        // clear m
        for (; j < counts; j += len) {
            string jsub = s.substr(j, len);
            if (m.count(jsub)) {
                ++m[jsub];
            }
        }
    }
public:
    vector<int> findSubstring(string s, vector<string>& words) {
        vector<int> res;
        if (words.size() == 0 || s.size() < words[0].size()) {
            return res;
        }
        unordered_map<string, int> words_map;
        for (auto w: words) {
            words_map.count(w) == 0 ? words_map[w] = 1 : ++words_map[w];
        }
        for (int i = 0; i < words[0].size(); ++i) {
            string sub = s.substr(i);
            find(sub, i, words[0].size(), words.size(), words_map, res);
        }
        return res;
    }
};
