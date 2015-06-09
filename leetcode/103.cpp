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
    vector<vector<int>> zigzagLevelOrder(TreeNode* root) {
        queue<TreeNode*> q({root, nullptr});
        vector<vector<int>> res;
        vector<int> tmp;
        bool left_to_right = true;
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
                if (!left_to_right) {
                    reverse(tmp.begin(), tmp.end());
                }
                res.push_back(tmp);
                tmp.clear();
                q.push(nullptr);
                left_to_right = !left_to_right;
            }
        }
        return res;
    }
};
