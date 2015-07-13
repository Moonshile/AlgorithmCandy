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
    bool findPath(TreeNode *root, TreeNode *node, vector<TreeNode*> &res) {
        if (root) {
            res.push_back(root);
            if (root == node || findPath(root->left, node, res) || findPath(root->right, node, res)) {
                return true;
            }
            res.pop_back();
        }
        return false;
    }
    
public:
    TreeNode* lowestCommonAncestor(TreeNode *root, TreeNode *p, TreeNode *q) {
        vector<TreeNode*> p_path, q_path;
        if (findPath(root, p, p_path) && findPath(root, q, q_path)) {
            for (int i = 0, n = min(p_path.size(), q_path.size()); i <= n; ++i) {
                if (i == n || p_path[i] != q_path[i]) {
                    return p_path[i - 1];
                }
            }
        }
        return nullptr;
    }
};
