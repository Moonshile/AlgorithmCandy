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
    int mdepth(TreeNode* root, int base) {
        if (root) {
            int mleft = mdepth(root->left, base + 1), mright = mdepth(root->right, base + 1);
            return !root->left || !root->right ? max(mleft, mright) : min(mleft, mright);
        }
        return base - 1;
    }
    
public:
    int minDepth(TreeNode* root) {
        return mdepth(root, 1);
    }
};
