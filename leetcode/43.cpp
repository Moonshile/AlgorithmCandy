class Solution {
private:
    struct BigInt {
        vector<long long> digits;
        const long long radix = 1000000000;
        
        BigInt() {}
        
        BigInt(string num) {
            string zeros(num.size()%9 == 0 ? 0 : 9 - num.size()%9, '0');
            num = zeros + num;
            for (int i = static_cast<int>(num.size()) - 9; i >= 0; i -= 9) {
                long long cur = 0;
                for (int j = 0; j < 9; ++j) {
                    cur = cur*10 + num[i + j] - '0';
                }
                digits.push_back(cur);
            }
        }
        
        string toString() const {
            stringstream ss;
            for (int i = static_cast<int>(digits.size()) - 1; i >= 0; --i) {
                stringstream tmp;
                tmp << digits[i];
                string d = tmp.str(), zeros(9 - d.size(), '0');
                ss << (i == static_cast<int>(digits.size()) - 1 ? "" : zeros) << d;
            }
            return ss.str() == "" ? "0" : ss.str();
        }
        
        const BigInt operator+(const BigInt &bi) const {
            BigInt res;
            long long cur = 0, len1 = digits.size(), len2 = bi.digits.size(), len = min(len1, len2);
            const BigInt &greater = len1 > len2 ? *this : bi, &lower = len1 > len2 ? bi : *this;
            for (int i = 0; i < len; ++i) {
                cur += greater.digits[i] + lower.digits[i];
                res.digits.push_back(cur%radix);
                cur /= radix;
            }
            for (unsigned int i = len; i < greater.digits.size(); ++i) {
                cur += greater.digits[i];
                res.digits.push_back(cur%radix);
                cur /= radix;
            }
            if (cur) {
                res.digits.push_back(cur);
            }
            return res;
        }
        
        const BigInt multiply_num(long long n) const {
            BigInt res;
            if (n == 0) {
                return res;
            }
            long long cur = 0;
            for (unsigned int i = 0; i < digits.size(); ++i) {
                cur += n*digits[i];
                res.digits.push_back(cur%radix);
                cur /= radix;
            }
            if (cur) {
                res.digits.push_back(cur);
            }
            return res;
        }
        
        const BigInt upgrade() {
            if (digits.size() > 0) {
                digits.insert(digits.begin(), 0);
                }
            return *this;
        }
        
        void copy(const BigInt &bi) {
            digits = bi.digits;
        }
        
        const BigInt operator*(const BigInt &bi) const {
            BigInt res;
            if (digits.size() == 0 || bi.digits.size() == 0) {
                return res;
            }
            int i = static_cast<int>(bi.digits.size()) - 1;
            res.copy(this->multiply_num(bi.digits[i]));
            for (--i; i >= 0; --i) {
                res.upgrade();
                res.copy(res + this->multiply_num(bi.digits[i]));
            }
            return res;
        }
    };
    
public:
    string multiply(string num1, string num2) {
        BigInt n1(num1), n2(num2);
        return (n1*n2).toString();
    }
};
