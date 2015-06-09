class Solution {
private:
    using sciter = string::const_iterator;
    
    bool validIP(string &s, int begin, int end) {
        if (end <= begin || end - begin > 3 || end - begin > 1 && s[begin] == '0') {
            return false;
        }
        int part = 0;
        for (auto i = begin; i != end; ++i) {
            part = part*10 + s[i] - '0';
        }
        return part <= 255;
    }
    
    string convert(string &s, vector<int> &positions) {
        stringstream ss;
        int i, m;
        for (i = 0, m = positions.size(); i < m - 2; ++i) {
            ss << s.substr(positions[i], positions[i + 1] - positions[i]) << '.';
        }
        ss << s.substr(positions[i]);
        return ss.str();
    }
    
public:
    vector<string> restoreIpAddresses(string s) {
        vector<string> res;
        if (s.size() < 4 || s.size() > 12) {
            return res;
        }
        vector<int> p{0, 0, 0, 0, s.size()};
        int i = 1;
        const int m = 3, n = 4;
        while (i > 0) {
            // forwarding
            for (; i < n; ++i) {
                p[i] = p[i - 1] + 1;
            }
            // success
            for (; p[m] - p[m - 1] <= 3; ++p[m]) {
                if (validIP(s, p[m - 1], p[m]) && validIP(s, p[m], p[n])) {
                    res.push_back(convert(s, p));
                }
            }
            // backwarding
            ++p[--i];
            while (!validIP(s, p[i - 1], p[i]) && i > 0) {
                ++p[--i];
            }
            if (i > 0) {
                ++i;
            }
        }
        return res;
    }
};
