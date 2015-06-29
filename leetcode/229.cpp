class Solution {
private:
    int count(vector<int> &nums, int target) {
        int res = 0;
        for (int i: nums) {
            if (i == target) {
                ++res;
            }
        }
        return res;
    }
    
public:
    vector<int> majorityElement(vector<int> &nums, int k) {
        if (k <= 1) {
            return vector<int>();
        }
        unordered_map<int, int> m;
        for (auto i: nums) {
            if (m.size() == k) {
                vector<int> keys_to_rm;
                for (auto &kv: m) {
                    --kv.second;
                    if (kv.second == 0) {
                        keys_to_rm.push_back(kv.first);
                    }
                }
                for (auto rm: keys_to_rm) {
                    m.erase(rm);
                }
            }
            if (m.count(i) == 0) {
                m[i] = 0;
            }
            ++m[i];
        }
        vector<int> res;
        for (auto &kv: m) {
            if (count(nums, kv.first) > nums.size()/k) {
                res.push_back(kv.first);
            }
        }
        return res;
    }
    
    vector<int> majorityElement(vector<int>& nums) {
        return majorityElement(nums, 3);
    }
};
