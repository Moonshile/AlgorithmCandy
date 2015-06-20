/**
 * Definition for a point.
 * struct Point {
 *     int x;
 *     int y;
 *     Point() : x(0), y(0) {}
 *     Point(int a, int b) : x(a), y(b) {}
 * };
 */
class Solution {
public:
    int maxPoints(vector<Point>& points) {
        int res = 0;
        for (int i = 0; i < points.size(); ++i) {
            unordered_map<double, int> m;
            int tmp = 0, bonus = 1;
            for (int j = i + 1; j < points.size(); ++j) {
                auto &pi = points[i], &pj = points[j];
                if (pi.x == pj.x && pi.y == pj.y) {
                    ++bonus;
                } else {
                    int delta_y = pi.x - pj.x == 0 ? abs(pi.y - pj.y) : pi.y - pj.y;
                    double slope = delta_y/static_cast<double>(pi.x - pj.x);
                    m[slope] = m.count(slope) == 0 ? 1 : m[slope] + 1;
                    tmp = max(tmp, m[slope]);
                }
            }
            res = max(res, tmp + bonus);
        }
        return res;
    }
};
