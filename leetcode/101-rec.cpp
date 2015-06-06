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
    inline bool areSymmetric(TreeNode* root1, TreeNode* root2) {
        return (!root1 && !root2)
        || (root1 && root2 && root1->val == root2->val 
            && areSymmetric(root1->left, root2->right) && areSymmetric(root1->right, root2->left));
    }
    
public:
    bool isSymmetric(TreeNode* root) {
        return root ? areSymmetric(root->left, root->right) : true;
    }
};
