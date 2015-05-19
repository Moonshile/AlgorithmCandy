class Solution {
private:
    using citer = vector<int>::const_iterator;
    void install(citer begin, citer end, unordered_map<int, vector<vector<citer>>> &m) {
        for (auto i = begin; i != end - 1 && i != end; ++i) {
            int iv = *i;
            for(; i + 2 != end && *(i + 2) == iv; ++i) {}
            for (auto j = i + 1; j != end; ) {
                int jv = *j, key = iv + jv;
                if (m.count(key) == 0) {
                    vector<vector<citer>> tmp;
                    m[key] = tmp;
                }
                vector<citer> pair{i, j};
                m[key].push_back(pair);
                if (jv == iv) {
                    ++i;
                }
                for (; j != end && *j == jv; ++j) {}
            }
        }
    }
    
    // with bin_search, complexity is (n^2)logn, else will be n^4
    vector<vector<citer>>::iterator upperBound(vector<vector<citer>> &pairs, citer target, citer base) {
        auto first = pairs.begin(), middle = first;
        auto len = pairs.size(), half = len;
        while (len > 0) {
            half = len >> 1;
            middle = first + half;
            if (target - base < (*middle)[0] - base) {
                len = half;
            } else {
                first = middle + 1;
                len = len - half - 1;
            }
        }
        return first != pairs.end() && target - base == (*first)[0] - base ? first + 1 : first;
    }
    
    void fourSumDo(citer begin, citer end, int target, unordered_map<int, vector<vector<citer>>> &m, vector<vector<int>> &res) {
        for (auto i = begin; i != end - 1;) {
            int iv = *i;
            for (auto j = i + 1; j != end; ) {
                int jv = *j, to_find = target - iv - jv;
                if (m.count(to_find) > 0) {
                    auto pairs = m[to_find];
                    for(auto start = upperBound(pairs, j, begin); start != pairs.end(); ++start) {
                        vector<int> tmp{iv, jv, *(*start)[0], *(*start)[1]};
                        res.push_back(tmp);
                    }
                }
                for (; j != end && *j == jv; ++j) {}
            }
            for (; i != end - 1 && *i == iv; ++i) {}
        }
    }
    
public:
    vector<vector<int>> fourSum(vector<int>& nums, int target) {
        vector<vector<int>> res;
        if (nums.size() < 4 || nums.size() > 99) {
            return res;
        }
        sort(nums.begin(), nums.end());
        unordered_map<int, vector<vector<citer>>> m;
        install(nums.begin(), nums.end(), m);
        fourSumDo(nums.begin(), nums.end(), target, m, res);
        return res;
    }
};
