class Solution {
public:
    int divide(int dividend, int divisor) {
        if (divisor == 0) {
            return INT_MAX;
        }
        long long dividend_t = abs(static_cast<long long>(dividend)), divisor_t = abs(static_cast<long long>(divisor)), part = 1, res = 0;
        bool positive = dividend > 0 && divisor > 0 || dividend < 0 && divisor < 0;
        vector<long long> items, parts;
        for (; divisor_t <= dividend_t; divisor_t += divisor_t, part += part) {
            items.push_back(divisor_t);
            parts.push_back(part);
        }
        auto i = lower_bound(items.begin(), items.end(), dividend_t);
        while (!items.empty() && !(i == items.begin() && *i != dividend_t)) {
            if (i != items.end() && *i == dividend_t) {
                res += parts[i - items.begin()];
                break;
            } else {
                res += parts[i - items.begin() - 1];
                dividend_t -= *(i - 1);
                i = lower_bound(items.begin(), items.end(), dividend_t);
            }
        }
        return positive && res > INT_MAX ? INT_MAX : static_cast<int>(positive ? res : -res);
    }
};
