class Solution {
public:
    int largestRectangleArea(vector<int>& height) {
        stack<int> ascend;
        int res = 0, i = 0;
        height.push_back(0);
        while (i < height.size()) {
            if (ascend.empty() || height[ascend.top()] <= height[i]) {
                ascend.push(i++);
            } else {
                int j = ascend.top();
                ascend.pop();
                res = max(res, height[j]*(ascend.empty() ? i : i - ascend.top() - 1));
            }
        }
        height.pop_back();
        return res;
    }
};
