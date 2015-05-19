class Solution {
public:
    int trap(vector<int>& height) {
        vector<int> heads = height;
        for (int max = 0, i = heads.size() - 1; i >= 0; --i) {
            max > heads[i] ? heads[i] = max : max = heads[i];
        }
        int res = 0;
        for (int i = 0, max = 0; i < height.size(); ++i) {
            max = max > height[i] ? max : height[i];
            int to_add = min(max, heads[i]) - height[i];
            if (to_add > 0) {
                res += to_add;
            }
        }
        return res;
    }
};
