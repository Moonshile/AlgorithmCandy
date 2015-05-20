class Solution {
private:
    void twoSumDo(vector<int>::const_iterator begin, vector<int>::const_iterator end, int target,
        unordered_map<int, vector<int>::const_iterator> &m, vector<vector<int>> &res) {
        // Because nums are sorted, so another must be greater than *i to ensure no duplications
        for (auto i = begin; i != end && target - *i >= *i;) {
            int another = target - *i;
            // m[another] is the last another, it should not be same as i to avoid duplications
            if (m.count(another) > 0 && m[another] - i > 0) {
                vector<int> to_add{-target, *i, another};
                res.push_back(to_add);
            }
            // Move to next different i to avoid duplicates
            while(i != end && target - *i == another) {
                ++i;
            }
        }
    }
    
public:
    vector<vector<int>> threeSum(vector<int>& nums) {
        sort(nums.begin(), nums.end());
        unordered_map<int, vector<int>::const_iterator> m;
        for (auto i = nums.begin(); i != nums.end(); ++i) {
            m[*i] = i;
        }
        vector<vector<int>> res;
        for (auto i = nums.begin(); i != nums.end() && *i < 1;) {
            int target = -*i;
            twoSumDo(i + 1, nums.end(), target, m, res);
            while(i != nums.end() && *i == -target) {
                ++i;
            }
        }
        return res;
    }
};
