class Solution {
public:
    int divide(int dividend, int divisor) {
        if (divisor == 0) {
            return INT_MAX;
        }
        bool positive = dividend > 0 && divisor > 0 || dividend < 0 && divisor < 0;
        long long dividend_t = abs(static_cast<long long>(dividend)), divisor_t = abs(static_cast<long long>(divisor)), res = 0, part = 1;
        while (divisor_t <= dividend_t) {
            divisor_t <<= 1;
            part <<= 1;
        }
        while (part && dividend_t) {
            while (divisor_t > dividend_t) {
                divisor_t >>= 1;
                part >>= 1;
            }
            dividend_t -= divisor_t;
            res += part;
        }
        return positive && res > INT_MAX ? INT_MAX : (positive ? res : -res);
    }
};
