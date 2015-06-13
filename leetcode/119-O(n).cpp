// O(n)
class Solution {
public:
    vector<int> getRow(int rowIndex) {
        vector<int> res(rowIndex + 1, 0);
        unsigned long long value = 1;
        for (int i = 0, m = rowIndex>>1; i <= m; ++i) {
            value = i == 0 ? 1 : (value%i == 0 ? value/i*(rowIndex - i + 1) : value*(rowIndex - i + 1)/i);
            res[i] = res[rowIndex - i] = static_cast<int>(value);
        }
        return res;
    }
};
