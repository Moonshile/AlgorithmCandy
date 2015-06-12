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
    void downtoLeaf(TreeNode* root, stack<TreeNode*> &s) {
        while (root) {
            if (root->right) {
                s.push(root->right);
            }
            root->right = root->left ? root->left : (s.empty() ? nullptr : s.top());
            auto tmp = root;
            root = root->left;
            tmp->left = nullptr;
        }
    }
    
    void preorder(TreeNode* root) {
        stack<TreeNode*> s;
        do {
            downtoLeaf(root, s);
            root = nullptr;
            if (!s.empty()) {
                root = s.top();
                s.pop();
            }
        } while (root);
    }
    
public:
    void flatten(TreeNode* root) {
        preorder(root);
    }
};
