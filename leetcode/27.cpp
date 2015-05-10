class Solution {
public:
    int removeElement(vector<int>& nums, int val) {
        for (auto i = nums.begin(); i != nums.end(); ++i) {
            if (*i == val) {
                for(; nums.end() - 1 != i && *(nums.end() - 1) == val; nums.pop_back());
                *i = *(nums.end() - 1);
                nums.pop_back();
            }
            if(i == nums.end()) {
                break;
            }
        }
        return nums.size();
    }
};