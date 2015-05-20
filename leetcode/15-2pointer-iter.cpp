class Solution {
private:
    using citer = vector<int>::const_iterator;
    vector<vector<int>> twoSumDo(citer begin, citer end, int target) {
        vector<vector<int>> res;
        citer first = begin, last = end - 1;
        while(first < last) {
            const int &fv = *first, &lv = *last, sum = fv + lv;
            if (sum == target) {
                vector<int> tmp{fv, lv};
                res.push_back(tmp);
                ++first;
                --last;
            } else {
                sum < target ? ++first : --last;
            }
            for (; first != begin && *first == *(first - 1); ++first) {}
            for (; last != end - 1 && *last == *(last + 1); --last) {}
        }
        return res;
    }
    
    vector<vector<int>> threeSumDo(citer begin, citer end, int target) {
        vector<vector<int>> res;
        for (auto i = begin; i != end;) {
            int iv = *i, to_find = target - iv;
            auto tmp = twoSumDo(i + 1, end, to_find);
            for (auto t: tmp) {
                t.insert(t.begin(), iv);
                res.push_back(t);
            }
            for (; i != end && *i == iv; ++i) {}
        }
        return res;
    }
    
public:
    vector<vector<int>> threeSum(vector<int>& nums) {
        sort(nums.begin(), nums.end());
        return threeSumDo(nums.begin(), nums.end(), 0);
    }
};
