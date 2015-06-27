class Solution {
public:
    bool containsNearbyAlmostDuplicate(vector<int>& nums, int k, int t) {
        multiset<long long> m;
        for (int i = 0; i < nums.size(); ++i) {
            if (i > k) {
                m.erase(nums[i - k - 1]);
            }
            auto lower = m.lower_bound(nums[i] - t);
            if (lower != m.cend() && *lower - nums[i] <= t) {
                return true;
            }
            m.insert(nums[i]);
        }
        return false;
    }
};
