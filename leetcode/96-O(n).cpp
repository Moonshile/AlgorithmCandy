// Catalan(n) = C(2n, n)/(n + 1) = A(2n, n - 1)/n!;
class Solution {
public:
    int numTrees(int n) {
        long long part1 = 1, part2 = 1;
        for (int i = 2; i <=n; ++i) {
            part1 *= n + i;
            part2 *= i;
            if (part1/part2*part2 == part1) {
                part1 /= part2;
                part2 = 1;
            }
        }
        return part1/part2;
    }
};
