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
    int maxSumToLeaf(TreeNode *root, int &max_path_sum) {
        if (root) {
            int lm = INT_MIN, rm = INT_MIN, left = maxSumToLeaf(root->left, lm), right = maxSumToLeaf(root->right, rm);
            max_path_sum = max(max(max_path_sum, left + right + root->val), max(lm, rm));
            return max(max(max(left, right), 0) + root->val, 0);
        }
        return 0;
    }
    
public:
    int maxPathSum(TreeNode *root) {
        int res = INT_MIN;
        maxSumToLeaf(root, res);
        return res;
    }
};
