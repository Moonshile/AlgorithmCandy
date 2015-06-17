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
    int sum(TreeNode *root, int cur) {
        if (root) {
            int next = cur*10 + root->val;
            int sumL = sum(root->left, next), sumR = sum(root->right, next);
            return sumL + sumR == 0 ? next : sumL + sumR;
        }
        return 0;
    }
    
public:
    int sumNumbers(TreeNode *root) {
        return sum(root, 0);
    }
};
