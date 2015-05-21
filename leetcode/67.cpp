class Solution {
public:
    string addBinary(string a, string b) {
        stringstream res;
        int len = max(a.size(), b.size()), m = min(a.size(), b.size());
        char carry = '0';
        string s(len - m, '0');
        a.size() < b.size() ? a = s + a : b = s + b;
        for (int i = len - 1; i >= 0; --i) {
            if (a[i] == '1' && b[i] == '1') {
                res << carry;
                carry = '1';
            } else if ((a[i] == '1' || b[i] == '1') && carry == '1') {
                res << '0';
                carry = '1';
            } else if (a[i] == '1' || b[i] == '1') {
                res << '1';
                carry = '0';
            } else {
                res << carry;
                carry = '0';
            }
        }
        if (carry == '1') {
            res << carry;
        }
        string sum = res.str();
        reverse(sum.begin(), sum.end());
        return sum;
    }
};
