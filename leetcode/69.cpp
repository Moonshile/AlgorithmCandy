class Solution {
private:
    const int MAX_ROOT = 46341;
public:
    int mySqrt(int x) {
        int first = 0, middle;
        int len = MAX_ROOT - first, half;
        while (len > 0) {
            half = len >> 1;
            middle = first + half;
            if (x <= middle*middle) {
                len = half;
            } else {
                first = middle + 1;
                len = len - half - 1;
            }
        }
        return first*first == x ? first : first - 1;
    }
};
