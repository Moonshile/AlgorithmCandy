/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode(int x) : val(x), left(NULL), right(NULL) {}
 * };
 */
class Solution {
private:
    inline void pushIfExists(TreeNode *node, queue<TreeNode*> &q) {
        if (node) {
            q.push(node);
        }
    }

public:
    vector<int> rightSideView(TreeNode *root) {
        vector<int> res;
        queue<TreeNode*> q;
        if (root) {
            q.push(root);
            q.push(nullptr);
        }
        while (!q.empty()) {
            auto node = q.front();
            q.pop();
            pushIfExists(node->left, q);
            pushIfExists(node->right, q);
            if (q.front() == nullptr) {
                res.push_back(node->val);
                q.pop();
                if (!q.empty()) {
                    q.push(nullptr);
                }
            }
        }
        return res;
    }
};
