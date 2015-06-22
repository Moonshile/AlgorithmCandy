class Solution {
private:
    stringstream ss;
    
    inline string numToStr(int num) {
        ss.str("");
        ss << num;
        return ss.str();
    }
    
    struct comparator {
        bool operator()(string s1, string s2) {
            int minLen = min(s1.size(), s2.size());
            for (int i = 0; i < minLen; ++i) {
                if (s1[i] != s2[i]) {
                    return s1[i] > s2[i];
                }
            }
            return s1 + s2 > s2 + s1;
        }
    } cmp;
    
public:
    string largestNumber(vector<int>& nums) {
        vector<string> strs;
        for (int n: nums) {
            strs.push_back(numToStr(n));
        }
        sort(strs.begin(), strs.end(), cmp);
        if (strs.size() > 0 && strs[0] == "0") {
            return strs[0];
        }
        stringstream ss;
        for (string s: strs) {
            ss << s;
        }
        return ss.str();
    }
};
