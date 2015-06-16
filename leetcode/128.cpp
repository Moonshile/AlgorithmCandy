class Solution {
public:
    int longestConsecutive(vector<int>& nums) {
        unordered_map<int, bool> m;
        int res = 0;
        for (int i: nums) {
            m[i] = false;
        }
        for (int i: nums) {
            if (m[i]) {
                continue;
            }
            int tmp = 0, post = i, pre = i - 1;
            while (m.count(post) > 0) {
                ++tmp;
                m[post++] = true;
            }
            while (m.count(pre) > 0) {
                ++tmp;
                m[pre--] = true;
            }
            res = max(res, tmp);
        }
        return res;
    }
};
