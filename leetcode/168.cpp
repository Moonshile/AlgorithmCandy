class Solution {
public:
    string convertToTitle(int n) {
        stringstream ss;
        do {
            n -= 1;
            ss << static_cast<char>(n%26 + 'A');
            n /= 26;
        } while (n);
        string res = ss.str();
        reverse(res.begin(), res.end());
        return res;
    }
};
