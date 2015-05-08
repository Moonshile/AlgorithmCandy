class Solution {
public:
    int romanToInt(string s) {
        int nums[256];
        char keys[] = {'I', 'V', 'X', 'L', 'C', 'D', 'M'};
        int values[] = {1, 5, 10, 50, 100, 500, 1000};
        for (int i = 0; i < 7; ++i) {
            nums[keys[i]] = values[i];
        }
        int res = 0;
        for (auto c = s.begin(), e = s.end(); c != e; ++c) {
            res += c + 1 != e && nums[*c] < nums[*(c + 1)] ? -nums[*c] : nums[*c];
        }
        return res;
    }
};