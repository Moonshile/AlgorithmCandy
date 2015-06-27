class Solution {
public:
    int maxProfit(int k, vector<int>& prices) {
        int res = 0, n = prices.size();
        // to get max profit, need maxK transactions
        // if maxK is lower than k, then get result
        int maxK = 0, maxP = 0;
        for (int i = 1, buy = 0; i < n; ++i) {
            while (i < n && prices[i] <= prices[i - 1]) {
                buy = i;
                ++i;
            }
            while (i < n && prices[i] >= prices[i - 1]) {
                ++i;
            }
            if (i - 1 > buy) {
                maxP += prices[i - 1] - prices[buy];
                ++maxK;
                buy = i;
            }
        }
        if (maxK <= k) {
            return maxP;
        }
        // else dp to get solution
        k = min(k, n);
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
};
