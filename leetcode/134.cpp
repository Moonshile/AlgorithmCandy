class Solution {
public:
    int canCompleteCircuit(vector<int>& gas, vector<int>& cost) {
        if (gas.size() == 0 || gas.size() != cost.size()) {
            return -1;
        }
        int n = gas.size(), i = n - 1, cur = gas[i] - cost[i];
        for (int j = 0; j < i; ++j) {
            while (cur < 0 && j < i) {
                --i;
                cur += gas[i] - cost[i];
            }
            cur += j < i ? gas[j] - cost[j] : 0;
        }
        return cur >= 0 ? i : -1;
    }
};
