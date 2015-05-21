/**
 * Definition for an interval.
 * struct Interval {
 *     int start;
 *     int end;
 *     Interval() : start(0), end(0) {}
 *     Interval(int s, int e) : start(s), end(e) {}
 * };
 */
class Solution {
private:
    struct Compare {
        bool operator()(const Interval &i1, const Interval &i2) const {
            return i1.start < i2.start;
        }
    }c;

public:
    vector<Interval> merge(vector<Interval>& intervals) {
        bool empty = true;
        Interval cur;
        vector<Interval> res;
        sort(intervals.begin(), intervals.end(), c);
        for (auto i: intervals) {
            if (empty) {
                cur.start = i.start;
                cur.end = i.end;
                empty = false;
            } else if (cur.end >= i.start) {
                cur.end = max(cur.end, i.end);
            } else {
                Interval tmp(cur.start, cur.end);
                res.push_back(tmp);
                cur.start = i.start;
                cur.end = i.end;
            }
        }
        if (!empty) {
            res.push_back(cur);
        }
        return res;
    }
};
