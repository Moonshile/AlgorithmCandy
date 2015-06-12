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
    bool balanced(TreeNode* root, int &height) {
        if (root) {
            int lh, rh;
            bool bLeft = balanced(root->left, lh), bRight = balanced(root->right, rh);
            if (bLeft && bRight && abs(lh - rh) <= 1) {
                height = max(lh, rh) + 1;
                return true;
            }
            return false;
        }
        height = -1;
        return true;
    }
    
public:
    bool isBalanced(TreeNode* root) {
        int height;
        return balanced(root, height);
    }
};
