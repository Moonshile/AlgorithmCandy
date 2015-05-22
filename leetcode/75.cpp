class Solution {
public:
    void sortColors(vector<int>& nums) {
        int first1 = -1, first2 = -1;
        auto begin = nums.begin();
        for (int i = 0; i < nums.size(); ++i) {
            switch (nums[i]) {
            case 0:
                if (first1 != -1) {
                    iter_swap(begin + first1, begin + i);
                    nums[first1 + 1] == 1 ? ++first1 : first1 = -1;
                    --i;
                } else if (first2 != -1) {
                    iter_swap(begin + first2, begin + i);
                    ++first2;
                }
                break;
            case 1:
                if (first1 == -1) {
                    first1 = i;
                    --i;
                } else if (first2 != -1) {
                    iter_swap(begin + first2, begin + i);
                    if (first2 == 0 || nums[first2 - 1] == 0) {
                        first1 = first2;
                    }
                    ++first2;
                }
                break;
            case 2:
                if (first2 == -1) {
                    first2 = i;
                }
                break;
            default:
                break;
            }
        }
    }
};
