class Solution {
public:
    int maxProfit(vector<int>& prices) {
        int res = 0, min_price = INT_MAX;
        for (int p: prices) {
            min_price = min(p, min_price);
            res = max(p - min_price, res);
        }
        return res;
    }
};
