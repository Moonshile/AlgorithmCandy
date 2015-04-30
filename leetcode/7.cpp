#include <iostream>
#include <vector>

using namespace std;

class Solution {
public:
    int reverse(int x) {
        int res = 0;
        bool positive = x >= 0 ? true : false;
        x = positive ? x : -x;
        // if x is -2147483648 then -x is also -2147483648
        // so the condition mustn't be != but >
        while(x > 0) {
            if (res*10/10 < res) {
                res = 0;
                break;
            }
            res = res*10 + x%10;
            x /= 10;
        }
        return positive ? res : -res;
    }
};

int main() {
    vector<int> tests = {123, 100, 1000000003, 1534236469, -123, -2147483648};
    Solution s;
    for(auto t: tests) {
        cout << t << " " << s.reverse(t) << endl;
    }
}
