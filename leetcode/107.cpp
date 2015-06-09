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
    inline void pushIfExists(vector<TreeNode*> &q, TreeNode *node) {
        if (node) {
            q.push_back(node);
        }
    }
    
public:
    vector<vector<int>> levelOrderBottom(TreeNode* root) {
        vector<TreeNode*> q;
        if (root) {
            q.push_back(nullptr);
            q.push_back(root);
        }
        for (int i = 0; i < q.size(); ++i) {
            if (q[i]) {
                pushIfExists(q, q[i]->right);
                pushIfExists(q, q[i]->left);
            } else if (i != q.size() - 1) {
                q.push_back(nullptr);
            }
        }
        vector<vector<int>> res;
        vector<int> tmp;
        for (int i = q.size() - 2; i >= 0; --i) {
            if (q[i]) {
                tmp.push_back(q[i]->val);
            } else {
                res.push_back(tmp);
                tmp.clear();
            }
        }
        return res;
    }
};
