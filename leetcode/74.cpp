class Solution {
private:
    using citer = vector<int>::const_iterator;
    
    citer lowerBound(citer first, citer last, int value) {
        citer middle;
        auto len = last - first, half = len;
        while (len > 0) {
            half = len >> 1;
            middle = first + half;
            if (value <= *middle) {
                len = half;
            } else {
                first = middle + 1;
                len = len - half - 1;
            }
        }
        return first;
    }
    
    bool binSearch(citer first, citer last, int value) {
        auto res = lowerBound(first, last, value);
        return res != last && *res == value;
    }
    
public:
    bool searchMatrix(vector<vector<int>>& matrix, int target) {
        auto outer_first = matrix.begin(), outer_last = matrix.end(), outer_middle = outer_first;
        auto outer_len = outer_last - outer_first, outer_half = outer_len;
        while (outer_len > 0) {
            outer_half = outer_len >> 1;
            outer_middle = outer_first + outer_half;
            auto inner_len = outer_middle->end() - outer_middle->begin();
            auto inner_middle = outer_middle->begin() + (inner_len >> 1);
            if (binSearch(outer_middle->begin(), outer_middle->end(), target)) {
                return true;
            } else if (inner_middle == outer_middle->end() || target <= *inner_middle) {
                outer_len = outer_half;
            } else {
                outer_first = outer_middle + 1;
                outer_len = outer_len - outer_half - 1;
            }
        }
        return false;
    }
};
