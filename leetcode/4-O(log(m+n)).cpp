#include <iostream>
#include <vector>

using namespace std;

/**
 * Reference: http://blog.csdn.net/yutianzuijin/article/details/11499917/
 */

class Solution {
private:
    using st = vector<int>::size_type;
    using it = vector<int>::const_iterator;

    double findKth(it a, st m, it b, st n, st k) {
        if (m > n) {
            return findKth(b, n, a, m, k);
        }
        if (m == 0) {
            return *(b + k);
        }
        if (k == 0) {
            return min(*a, *b);
        }
        st pa = min(k/2, m - 1);
        st pb = k - pa - 1;
        if (*(a + pa) < *(b + pb)) {
            return findKth(a + pa + 1, m - pa - 1, b, n, k - pa - 1);
        } else if (*(a + pa) > *(b + pb)) {
            return findKth(a, m, b + pb + 1, n - pb - 1, k - pb - 1);
        }
        return *(a + pa);
    }

public:
    double findMedianSortedArrays(vector<int>& nums1, vector<int>& nums2) {
        st total = nums1.size() + nums2.size();
        if (total & 0x1) {
            return findKth(nums1.begin(), nums1.size(), nums2.begin(), nums2.size(), total/2);
        } else {
            double r1 = findKth(nums1.begin(), nums1.size(), nums2.begin(), nums2.size(), total/2 - 1);
            double r2 = findKth(nums1.begin(), nums1.size(), nums2.begin(), nums2.size(), total/2);
            return (r1 + r2)/2;
        }
    }
};

int main() {
    Solution s;
    vector<int> A;
    vector<int> B = {1};
    printf("%lf\n", s.findMedianSortedArrays(A, B));
    return 0;
}

