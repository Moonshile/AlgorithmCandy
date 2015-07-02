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
    void downtoLeaf(TreeNode *root, stack<TreeNode*> &s) {
        while (root) {
            s.push(root->right);
            s.push(root);
            root = root->left;
        }
    }
    
    int inorder(TreeNode *root, int k) {
        stack<TreeNode*> s;
        int i = 0;
        downtoLeaf(root, s);
        while (!s.empty()) {
            root = s.top();
            s.pop();
            ++i;
            if (i == k) {
                return root->val;
            }
            root = s.top();
            s.pop();
            downtoLeaf(root, s);
        }
    }
    
public:
    int kthSmallest(TreeNode *root, int k) {
        return inorder(root, k);
    }
};
