class Solution {
public:
    string minWindow(string s, string t) {
        int first = 0, last = -1, count = 0, start = -1, len = INT_MAX;
        unordered_map<char, int> m_base, m_occur;
        for (auto c: t) {
            m_base[c] = m_base.count(c) == 0 ? 0 : m_base[c] + 1;
            m_occur[c] = 0;
        }
        for (int i = 0; i < s.size(); ++i) {
            if (m_base.count(s[i]) == 0) {
                continue;
            }
            ++m_occur[s[i]];
            last = i;
            if (count != t.size() && m_occur[s[i]] <= m_base[s[i]]) { // inc count only when the character hasn't been used up
                ++count;
            }
            if (count == t.size()) { // update the window, even when this is its first occurance
                for (; m_base.count(s[first]) == 0 || m_occur[s[first]] - 1 >= m_base[s[first]]; ++first) {
                    if (m_base.count(s[first]) > 0) {
                        --m_occur[s[first]];
                    }
                }
                if (last - first + 1 < len) {
                    start = first;
                    len = last - first + 1;
                }
            }
        }
        return start == -1 ? "" : s.substr(start, len);
    }
};
