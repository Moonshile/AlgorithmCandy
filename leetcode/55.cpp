class Solution {
public:
    bool canJump(vector<int>& nums) {
        int cur_reachable = 0, next_reachable = 0;
        for (int i = 0; i < nums.size(); ++i) {
            if (cur_reachable < i) {
                cur_reachable = next_reachable;
            }
            next_reachable = max(next_reachable, nums[i] + i);
            if (cur_reachable == i && next_reachable == i && nums.size() - 1 != i) {
                return false;
            }
        }
        return true;
    }
};
