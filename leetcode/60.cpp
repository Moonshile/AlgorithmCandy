class Solution {
public:
    string getPermutation(int n, int k) {
        vector<int> nums;
        int total = 1;
        for (int i = 1; i <= n; ++i) {
            nums.push_back(i);
            total *= i;
        }
        --k;
        stringstream res;
        while (n > 0) {
            total /= n;
            res << nums[k/total];
            nums.erase(nums.begin() + k/total);
            k %= total;
            --n;
        }
        return res.str();
    }
};
