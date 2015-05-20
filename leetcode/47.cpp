class Solution {
private:
    bool next_permutation(vector<int>::iterator first, vector<int>::iterator last) {
        if (first == last || first + 1 == last) {
            return false;
        }
        auto i = last - 1;
        while (true) {
            auto ii = i--;
            if (*i < *ii) {
                auto j = last - 1;
                for (; *j <= *i; --j) {}
                iter_swap(i, j);
                reverse(ii, last);
                return true;
            } else if (i == first) {
                reverse(first, last);
                return false;
            }
        }
    }
public:
    vector<vector<int>> permuteUnique(vector<int>& nums) {
        sort(nums.begin(), nums.end());
        vector<vector<int>> res;
        do {
            vector<int> t = nums;
            res.push_back(t);
        } while (next_permutation(nums.begin(), nums.end()));
        return res;
    }
};
