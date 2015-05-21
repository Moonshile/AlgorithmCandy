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
public:
    vector<Interval> insert(vector<Interval>& intervals, Interval newInterval) {
        vector<Interval> res;
        bool first = true;
        for (auto i: intervals) {
            if (i.end < newInterval.start) {
                res.push_back(i);
            } else if (i.start > newInterval.end && first) {
                res.push_back(newInterval);
                res.push_back(i);
                first = false;
            } else if (i.start > newInterval.end) {
                res.push_back(i);
            } else {
                newInterval.start = min(newInterval.start, i.start);
                newInterval.end = max(newInterval.end, i.end);
            }
        }
        if (first) {
            res.push_back(newInterval);
        }
        return res;
    }
};
