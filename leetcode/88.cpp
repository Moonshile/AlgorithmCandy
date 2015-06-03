class Solution {
public:
    void merge(vector<int>& nums1, int m, vector<int>& nums2, int n) {
        int i = m - 1, j = n - 1, t = m + n - 1;
        while (t >= 0) {
            nums1[t--] = i < 0 || j >= 0 && nums2[j] >= nums1[i] ? nums2[j--] : nums1[i--];
        }
    }
};
