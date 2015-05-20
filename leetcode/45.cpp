class Solution {
public:
    int jump(vector<int>& nums) {
        int res = 0, cur_reachable = 0, next_reachable = 0;
        for(int i = 0; i < nums.size(); ++i) {
            if(cur_reachable < i) {
                ++res;
                cur_reachable = next_reachable;
            }
            next_reachable = max(next_reachable, nums[i] + i);
        }
        return res;
    }
};
