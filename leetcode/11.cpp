class Solution {
public:
    int maxArea(vector<int>& height) {
        vector<int>::const_iterator f = height.begin(), b = height.end() - 1;
        int max = 0;
        while (f < b) {
            max = max > min(*f, *b)*(b - f) ? max : min(*f, *b)*(b - f);
            *f < *b ? ++f : --b;
        }
        return max;
    }
};