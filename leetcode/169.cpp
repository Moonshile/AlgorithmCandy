class Solution {
public:
    int majorityElement(vector<int>& nums) {
        vector<int> tmp(nums);
        int len = tmp.size();
        while (len > 1) {
            int i = 0;
            for (int j = 0; j < len; j += 2) {
                if ((j == len - 1 && (i&1) == 0) || j < len - 1 && tmp[j] == tmp[j + 1]) {
                    tmp[i++] = tmp[j];
                }
            }
            len = i;
        }
        return tmp[0];
    }
};
