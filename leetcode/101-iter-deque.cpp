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
        deque<TreeNode*> q{root1, root2};
        while (!q.empty()) {
            TreeNode *ln = q.front(), *rn = q.back();
            q.pop_front();
            q.pop_back();
            if (ln && rn && ln->val == rn->val) {
                q.push_front(ln->left);
                q.push_front(ln->right);
                q.push_back(rn->right);
                q.push_back(rn->left);
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
