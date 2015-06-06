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
    void doInorderTraversal(TreeNode* root, vector<int> &res) {
        if (root) {
            doInorderTraversal(root->left, res);
            res.push_back(root->val);
            doInorderTraversal(root->right, res);
        }
    }
    
public:
    vector<int> inorderTraversal(TreeNode* root) {
        vector<int> res;
        doInorderTraversal(root, res);
        return res;
    }
};
