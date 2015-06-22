class Solution {
private:
    inline void mark(vector<bool> &is_prime, int i, int n) {
        for (int j = i*i; j < n; j += i) {
            is_prime[j] = false;
        }
    }
    
public:
    int countPrimes(int n) {
        vector<bool> is_prime(n, true);
        for (int i = 2; i*i < n; ++i) {
            if (is_prime[i]) {
                mark(is_prime, i, n);
            }
        }
        int res = 0;
        for (int i = 2; i < n; ++i) {
            if (is_prime[i]) {
                ++res;
            }
        }
        return res;
    }
};
