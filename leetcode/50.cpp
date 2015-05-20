class Solution {
public:
    double myPow(double x, int n) {
        if (x == 0) {
            return 0;
        } else if (n == 0) {
            return 1.0f;
        } else if (n < 0) {
            return 1/myPow(x, -(1 + n))/x;
        } else if (n%2 == 1) {
            double p = myPow(x, (n - 1)>>1);
            return x*p*p;
        } else {
            double p = myPow(x, n>>1);
            return p*p;
        }
    }
};
