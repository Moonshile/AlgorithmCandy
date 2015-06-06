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
public:
    vector<vector<int>> levelOrder(TreeNode* root) {
        queue<TreeNode*> q({root, nullptr});
        vector<vector<int>> res;
        vector<int> tmp;
        while(!q.empty()) {
            auto node = q.front();
            q.pop();
            if (node) {
                tmp.push_back(node->val);
                if (node->left) {
                    q.push(node->left);
                }
                if (node->right) {
                    q.push(node->right);
                }
            } else if (!tmp.empty()) {
                res.push_back(tmp);
                tmp.clear();
                q.push(nullptr);
            }
        }
        return res;
    }
};
