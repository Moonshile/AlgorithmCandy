class Solution {
public:
    bool containsDuplicate(vector<int>& nums) {
        unordered_set<int> m;
        for (int i: nums) {
            if (m.count(i) > 0) {
                return true;
            }
            m.insert(i);
        }
        return false;
    }
};
