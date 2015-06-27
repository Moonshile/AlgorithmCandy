class Solution {
public:
    vector<pair<int, int>> getSkyline(vector<vector<int>>& buildings) {
        vector<pair<int, int>> heights;
        for (auto &b: buildings) {
            heights.push_back({b[0], -b[2]});
            heights.push_back({b[1], b[2]});
        }
        sort(heights.begin(), heights.end());
        multiset<int> height_sequence({0});
        vector<pair<int, int>> res;
        int pre_max_height = 0, cur_max_height;
        for (unsigned int i = 0; i < heights.size(); ++i) {
            auto &p = heights[i];
            if (p.second < 0) {
                height_sequence.insert(-p.second);
            } else {
                height_sequence.erase(height_sequence.find(p.second));
            }
            cur_max_height = *height_sequence.crbegin();
            if (pre_max_height != cur_max_height) {
                res.push_back({p.first, cur_max_height});
                pre_max_height = cur_max_height;
            }
        }
        return res;
    }
};
