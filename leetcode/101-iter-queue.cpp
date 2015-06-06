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
    bool areSymmetric(TreeNode* root1, TreeNode* root2) {
        queue<TreeNode*> left({root1}), right({root2});
        while (!left.empty()) {
            TreeNode *ln = left.front(), *rn = right.front();
            left.pop();
            right.pop();
            if (ln && rn && ln->val == rn->val) {
                left.push(ln->left);
                left.push(ln->right);
                right.push(rn->right);
                right.push(rn->left);
            } else if (!ln && !rn) {
                continue;
            } else {
                return false;
            }
        }
        return true;
    }
    
public:
    bool isSymmetric(TreeNode* root) {
        return root ? areSymmetric(root->left, root->right) : true;
    }
};
