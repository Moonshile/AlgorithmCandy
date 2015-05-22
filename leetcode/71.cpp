class Solution {
public:
    string simplifyPath(string path) {
        stack<string> s, t;
        for (int i = 1, len = 0, last = 1; i < path.size(); ++i, ++len) {
            if (path[i] == '/' || i == path.size() - 1) {
                if (len > 0 || i == path.size() - 1) {
                    string f = path.substr(last, i == path.size() - 1 && path[i] != '/' ? len + 1 : len);
                    if (f == ".." && s.size() > 0) {
                        s.pop();
                    } else if (f != "." && f != ".." && f != "") {
                        s.push(f);
                    }
                }
                len = -1;
                last = i + 1;
            }
        }
        while (s.size() > 0) {
            t.push(s.top());
            s.pop();
        }
        stringstream res;
        while (t.size() > 0) {
            res << "/" << t.top();
            t.pop();
        }
        return res.str() == "" ? "/" : res.str();
    }
};
