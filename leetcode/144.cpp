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
    void downtoLeaf(TreeNode *root, stack<TreeNode*> &s, vector<int> &res) {
        while (root) {
            res.push_back(root->val);
            if (root->right) {
                s.push(root->right);
            }
            root = root->left;
        }
    }
    
public:
    vector<int> preorderTraversal(TreeNode* root) {
        stack<TreeNode*> s({root});
        vector<int> res;
        while (!s.empty()) {
            root = s.top();
            s.pop();
            downtoLeaf(root, s, res);
        }
        return res;
    }
};
