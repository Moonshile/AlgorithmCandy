class Solution {
private:
    inline int next(int n) {
        int res = 0;
        while (n) {
            res += (n%10)*(n%10);
            n /= 10;
        }
        return res;
    }
    
public:
    bool isHappy(int n) {
        unordered_set<int> accessed;
        while (accessed.count(n) == 0) {
            accessed.insert(n);
            n = next(n);
        }
        return n == 1;
    }
};
