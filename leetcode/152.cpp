class Solution {
public:
    int maxProduct(vector<int>& nums) {
        int res = INT_MIN, local_max = 1, local_min = 1;
        for (auto i: nums) {
            int tmp = local_max;
            local_max = max(max(i, tmp*i), local_min*i);
            local_min = min(min(i, tmp*i), local_min*i);
            res = max(res, local_max);
        }
        return res;
    }
};
