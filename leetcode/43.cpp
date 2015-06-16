
#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <stdexcept>
#include <cctype>
#include <algorithm>

using namespace std;

class not_valid_number: public runtime_error {
public:
    not_valid_number(const string &s): runtime_error(s + " is not a valid number") {}
};

class wrong_scalar_range: public runtime_error {
public:
    wrong_scalar_range(long long scalar):
      runtime_error(scalar + "is not in range [0, 999999999]") { }
};

class BigInt {
    friend const BigInt operator+(const BigInt &bi1, const BigInt &bi2);
    friend const BigInt scalar_multiply(const BigInt &bi, long long scalar, int base);
    friend const BigInt operator*(const BigInt &bi1, const BigInt &bi2);
private:
    // store digits from lower to higher
    vector<long long> digits;
    bool positive;

    static const long long radix() {
        return 1000000000;
    }

    static const int max_unit() {
        return 9;
    }

    void minify() {
        while (digits.size() > 1 && digits.back() == 0) {
            digits.pop_back();
        }
    }

public:
    explicit BigInt(const string &num): digits() {
        if ((num.size() == 1 && !isdigit(num[0])) ||
            (num.size() > 1 && !isdigit(num[0]) && num[0] != '-' && num[0] != '+')) {
            throw not_valid_number(num);
        } else if (num.size() == 0) {
            digits.push_back(0);
        } else {
            positive = num[0] == '-' ? false : true;
            int end = isdigit(num[0]) ? 0 : 1;
            while (isspace(num[end])) {
                ++end;
            }
            long long cur = 0;
            for (int i = static_cast<int>(num.size()) - 1, j = 1; i >= end; --i) {
                if (isdigit(num[i])) {
                    cur += (num[i] - '0')*j;
                    j *= 10;
                    if (j == radix() || i == end) {
                        j = 1;
                        digits.push_back(cur);
                        cur = 0;
                    }
                } else {
                    throw not_valid_number(num);
                }
            }
        }
    }

    BigInt(): BigInt("0") { }

    BigInt(const vector<long long> &ds, bool pos=true): digits(ds), positive(pos) {
        for (auto d: ds) {
            if (d >= radix() || d < 0) {
                throw not_valid_number("The array");
            }
        }
    }

    BigInt(const BigInt &big_int, bool pos=true): BigInt(big_int.digits, pos) { }

    string toString() const {
        stringstream ss, tmp;
        if (!positive) {
            ss << "-";
        }
        for (int n = static_cast<int>(digits.size()) - 1, i = n; i >= 0; --i) {
            tmp.str("");
            tmp << digits[i];
            string d = tmp.str(), zeros(max_unit() - d.size(), '0');
            ss << (i == n ? "" : zeros) << d;
        }
        return ss.str() == "" ? "0" : ss.str();
    }
};

const BigInt operator+(const BigInt &bi1, const BigInt &bi2) {
    // TODO handle negative inputs
    BigInt res(vector<long long>(max(bi1.digits.size(), bi2.digits.size()), 0));
    long long carry = 0;
    for (unsigned int i = 0; i < res.digits.size(); ++i) {
        if (i < bi1.digits.size()) {
            res.digits[i] += bi1.digits[i];
        }
        if (i < bi2.digits.size()) {
            res.digits[i] += bi2.digits[i];
        }
        res.digits[i] += carry;
        carry = res.digits[i]/BigInt::radix();
        res.digits[i] %= BigInt::radix();
    }
    if (carry) {
        res.digits.push_back(carry);
    }
    res.minify();
    return res;
}

const BigInt scalar_multiply(const BigInt &bi, long long scalar, int base) {
    if (abs(scalar) >= BigInt::radix()) {
        throw wrong_scalar_range(scalar);
    }
    bool positive = (bi.positive && scalar >= 0) || (!bi.positive && scalar < 0);
    scalar = abs(scalar);
    BigInt res(vector<long long>(bi.digits.size() + base, 0), positive);
    long long carry = 0;
    for (unsigned int i = base; i < res.digits.size(); ++i) {
        res.digits[i] += carry + scalar*bi.digits[i - base];
        carry = res.digits[i]/BigInt::radix();
        res.digits[i] %= BigInt::radix();
    }
    if (carry) {
        res.digits.push_back(carry);
    }
    res.minify();
    return res;
}

const BigInt operator*(const BigInt &bi1, const BigInt &bi2) {
    BigInt res;
    for (unsigned int i = 0; i < bi2.digits.size(); ++i) {
        res = res + scalar_multiply(bi1, bi2.digits[i], i);
    }
    res.minify();
    res.positive = !(bi1.positive ^ bi2.positive);
    return res;
}

class Solution {
public:
    string multiply(string num1, string num2) {
        BigInt n1(num1), n2(num2);
        return (n1*n2).toString();
    }
};

int main() {
    Solution s;
    cout << s.multiply("-6913259244", "-71103343") << endl;
}
