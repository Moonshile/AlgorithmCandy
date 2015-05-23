class Solution {
private:
    void testToken(stack<string> &s, string f) {
        if (f == ".." && s.size() > 0) {
            s.pop();
        } else if (f != "." && f != ".." && f != "") {
            s.push(f);
        }
    }
public:
    string simplifyPath(string path) {
        stack<string> s, t;
        int len = 0, last = 1;
        for (int i = 1; i < path.size(); ++i) {
            if (path[i] == '/') {
                testToken(s, path.substr(last, len));
                len = 0;
                last = i + 1;
            } else {
                ++len;
            }
        }
        testToken(s, path.substr(last, len));
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
