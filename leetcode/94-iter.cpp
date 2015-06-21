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
        downtoLeaf(root, nodes);
        while (!nodes.empty()) {
            res.push_back(nodes.top()->val);
            nodes.pop();
            root = nodes.top();
            nodes.pop();
            downtoLeaf(root, nodes);
        }
        return res;
    }
};
