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
            s.push(root);
            s.push(root->right);
            root = root->left;
        }
    }
    
public:
    vector<int> postorderTraversal(TreeNode *root) {
        stack<TreeNode*> s({root});
        vector<int> res;
        while (!s.empty()) {
            root = s.top();
            s.pop();
            downtoLeaf(root, s);
            while (!s.empty() && s.top() && s.top()->right == root) {
                root = s.top();
                s.pop();
                res.push_back(root->val);
            }
        }
        return res;
    }
};
