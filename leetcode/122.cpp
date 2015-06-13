class Solution {
public:
    int maxProfit(vector<int>& prices) {
        int res = 0;
        for (int i = 1, n = prices.size(); i < n; ++i) {
            if (prices[i] > prices[i - 1]) {
                res += prices[i] - prices[i - 1];
            }
        }
        return res;
    }
};
