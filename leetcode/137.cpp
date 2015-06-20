class Solution {
public:
    int singleNumber(vector<int>& nums) {
        vector<int> bits(sizeof(int)*8, 0);
        for (int num: nums) {
            for (int i = 1, j = 0; i != 0; i <<= 1) {
                bits[j++] += num & i ? 1 : 0;
            }
        }
        int res = 0;
        for (auto b = bits.crbegin(); b != bits.crend(); ++b) {
            res = (res << 1) | (*b%3 ? 1 : 0);
        }
        return res;
    }
};
