class Solution {
private:
    static constexpr int bucketNum() { return 256; }
    static constexpr int loopCount() { return sizeof(int)*2; }
    
    inline int getAt(int num, int shift) {
        return (num>>shift)&0xf;
    }

    void radixSort(vector<int> &nums) {
        for (int i = 0; i < loopCount(); ++i) {
            vector<vector<int>> buckets(bucketNum());
            for (int n: nums) {
                buckets[getAt(n, i<<2)].push_back(n);
            }
            int j = 0;
            for (auto &bucket: buckets) {
                for (int n: bucket) {
                    nums[j++] = n;
                }
            }
        }
    }
    
public:
    int maximumGap(vector<int> &nums) {
        radixSort(nums);
        int res = 0;
        for (int i = 0; i + 1 < nums.size(); ++i) {
            res = max(res, nums[i + 1] - nums[i]);
        }
        return res;
    }
};
