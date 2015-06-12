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
    bool pathSum(TreeNode* root, int sum) {
        if (root) {
            bool sl = pathSum(root->left, sum - root->val), sr = pathSum(root->right, sum - root->val);
            return !root->left && root->right ? sr : (root->left && !root->right ? sl : sl || sr);
        }
        return sum == 0;
    }
    
public:
    bool hasPathSum(TreeNode* root, int sum) {
        return root ? pathSum(root, sum) : false;
    }
};
