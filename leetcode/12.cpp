class Solution {
private:
    vector<string> gen(const string &one, const string &five, const string &ten) {
        vector<string> res{one, one+one, one+one+one, one+five, five, 
            five+one, five+one+one, five+one+one+one, one+ten};
        return res;
    }
public:
    string intToRoman(int num) {
        vector<vector<string>> nums{gen("I", "V", "X"), gen("X", "L", "C"), 
            gen("C", "D", "M"), gen("M", "A", "B")};
        string res;
        int index = -1, next = 0;
        while (num > 0) {
            next = num%10;
            num /= 10;
            ++index;
            if (next) {
                res = nums[index][next - 1] + res;
            }
        }
        return res;
    }
};