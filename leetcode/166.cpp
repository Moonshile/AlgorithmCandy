class Solution {
public:
    string fractionToDecimal(int numerator, int denominator) {
        long long num = numerator, deno = denominator;
        stringstream ss;
        if (num > 0 && deno < 0 || num < 0 && deno > 0) {
            ss << '-';
        }
        num = abs(num);
        deno = abs(deno);
        ss << (num/deno);
        num = num%deno*10;
        unordered_set<long long> nums_met;
        vector<long long> nums, quots;
        while (num && nums_met.count(num) == 0) {
            nums_met.insert(num);
            nums.push_back(num);
            quots.push_back(num/deno);
            num = num%deno*10;
        }
        if (quots.size() > 0) {
            ss << '.';
            for (int i = 0; i < nums.size(); ++i) {
                if (nums[i] == num) {
                    ss << '(';
                }
                ss << quots[i];
            }
            if (num) {
                ss << ')';
            }
        }
        return ss.str();
    }
};
