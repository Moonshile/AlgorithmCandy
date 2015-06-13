// Reference: http://tech.ddvip.com/2014-08/1407214078212324.html
class Solution {
private:
    int maxProfitWithKTransactions(vector<int> &prices, int k) {
        int res = 0;
        vector<int> global(k + 1, 0), local(k + 1, 0);
        for (int i = 0, n = prices.size(); i < n - 1; ++i) {
            int diff = prices[i + 1] - prices[i];
            for (int j = k; j > 0; --j) {
                local[j] = max(global[j - 1] + max(diff, 0), local[j] + diff);
                global[j] = max(global[j], local[j]);
            }
        }
        return global[k];
    }
    
public:
    int maxProfit(vector<int>& prices) {
        return maxProfitWithKTransactions(prices, 2);
    }
};
