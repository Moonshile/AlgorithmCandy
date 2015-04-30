#include <iostream>
#include <vector>
#include <string>
#include <cctype>

using namespace std;

class Solution {
private:
    const int INT_MAX = 2147483647;
    const int INT_MIN = -2147483648;

    inline int charToDigit(char c) {
        return c - '0';
    }

public:
    int myAtoi(string str) {
        auto it = str.cbegin();
        for(; it != str.cend() && isspace(*it); ++it);
        if(it == str.cend() ||
            !(isdigit(*it) || *it == '+' || *it == '-') ||
            ((*it == '+' || *it == '-') && it + 1 != str.cend() && !isdigit(*(it + 1)))) {
            return 0;
        }
        bool positive = *it == '-' ? false : true;
        if(!isdigit(*it)) {
            ++it;
        }
        int res = 0, res_tmp;
        for(; it != str.cend() && isdigit(*it); ++it) {
            res_tmp = res;
            res = res*10 + (positive ? charToDigit(*it) : -charToDigit(*it));
            if((positive && res/10 < res_tmp) || (!positive && res/10 > res_tmp)) {
                return positive ? INT_MAX : INT_MIN;
            }
        }
        return res;
    }
};

int main() {
    vector<string> tests = {"+-2", "     10522545459", "-2147483649"};
    Solution s;
    for(auto t: tests) {
        cout << t << " " << s.myAtoi(t) << endl;
    }
    return 0;
}
