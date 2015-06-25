class Solution {
private:
    struct Comparator {
        bool operator()(int n1, int n2) {
            return n1 > n2;
        }
    };

public:
    int findKthLargest(vector<int>& nums, int k) {
        priority_queue<int, vector<int>, Comparator> q;
        for (int i: nums) {
            if (q.size() == k && q.top() < i) {
                q.pop();
                q.push(i);
            } else if (q.size() < k) {
                q.push(i);
            }
        }
        return q.top();
    }
};
