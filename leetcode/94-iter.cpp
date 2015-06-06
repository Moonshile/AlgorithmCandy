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
    void downtoLeaf(TreeNode* root, stack<TreeNode*> &nodes) {
        while (root) {
            nodes.push(root->right);
            nodes.push(root);
            root = root->left;
        }
    }
    
public:
    vector<int> inorderTraversal(TreeNode* root) {
        vector<int> res;
        stack<TreeNode*> nodes;
        do {
            downtoLeaf(root, nodes);
            root = nullptr;
            while (!nodes.empty() && !root) {
                root = nodes.top();
                nodes.pop();
                res.push_back(root->val);
                root = nodes.top();
                nodes.pop();
            }
        } while (root);
        return res;
    }
};
