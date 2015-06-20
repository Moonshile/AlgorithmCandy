class Solution {
public:
    int candy(vector<int>& ratings) {
        int last_max = 0, last_max_candy = 0, res = 0, cur = 0;
        for (int i = 0; i < ratings.size(); ++i) {
            if (i == 0 || ratings[i] >= ratings[i - 1]) {
                last_max = i;
                last_max_candy = cur = ratings[i] == ratings[i - 1] ? 1 : cur + 1;
            } else {
                cur = 1;
                res += i - last_max - (i - last_max >= last_max_candy ? 0 : 1);
            }
            res += cur;
        }
        return res;
    }
};
