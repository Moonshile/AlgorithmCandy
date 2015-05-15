class Solution {
private:
    void twoSumDo(vector<int>::const_iterator begin, vector<int>::const_iterator end, int target,
        unordered_map<int, vector<int>::const_iterator> &m, vector<vector<int>> &res) {
        for (auto i = begin; i != end; ++i) {
            int another = target - *i;
            if (m.count(another) > 0 && m[another] - i > 0) {
                vector<int> to_add{static_cast<int>(i - begin) + 1, static_cast<int>(m[another] - begin) + 1};
                res.push_back(to_add);
            }
        }
    }
public:
    vector<int> twoSum(vector<int>& nums, int target) {
        unordered_map<int, vector<int>::const_iterator> m;
        for (auto i = nums.begin(); i != nums.end(); ++i) {
            m[*i] = i;
        }
        vector<vector<int>> res;
        twoSumDo(nums.begin(), nums.end(), target, m, res);
        return res[0];
    }
};
