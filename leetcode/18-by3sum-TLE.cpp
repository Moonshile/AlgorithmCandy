class Solution {
private:
    void twoSumDo(vector<int>::const_iterator begin, vector<int>::const_iterator end, int base0, int base1, int target, 
        unordered_map<int, vector<int>::const_iterator> &m, vector<vector<int>> &res) {
        // Because nums are sorted, so another must be greater than *i to ensure no duplications
        for (auto i = begin; i != end && target - *i >= *i;) {
            int another = target - *i;
            // m[another] is the last another, it should not be same as i to avoid duplications
            if (m.count(another) > 0 && m[another] - i > 0) {
                vector<int> to_add{base0, base1, *i, another};
                res.push_back(to_add);
            }
            // Move to next different i to avoid duplicates
            while(i != end && target - *i == another) {
                ++i;
            }
        }
    }
    
    void threeSumDo(vector<int>::const_iterator begin, vector<int>::const_iterator end, int base, int target, 
    unordered_map<int, vector<int>::const_iterator> &m, vector<vector<int>> &res) {
        for (auto i = begin; i != end;) {
            int iv = *i, to_find = target - iv;
            twoSumDo(i + 1, end, base, iv, to_find, m, res);
            for (; i != end && *i == iv; ++i) {}
        }
    }
    
    void fourSumDo(vector<int>::const_iterator begin, vector<int>::const_iterator end, int target, 
    unordered_map<int, vector<int>::const_iterator> &m, vector<vector<int>> &res) {
        for (auto i = begin; i != end;) {
            int iv = *i, to_find = target - iv;
            threeSumDo(i + 1, end, iv, to_find, m, res);
            for (; i != end && *i == iv; ++i) {}
        }
    }
    
public:
    vector<vector<int>> fourSum(vector<int>& nums, int target) {
        sort(nums.begin(), nums.end());
        unordered_map<int, vector<int>::const_iterator> m;
        for (auto i = nums.begin(); i != nums.end(); ++i) {
            m[*i] = i;
        }
        vector<vector<int>> res;
        if (nums.size() > 60) {return res;}
        fourSumDo(nums.begin(), nums.end(), target, m, res);
        return res;
    }
};
