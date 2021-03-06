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
    
    bool validInorderTraversal(TreeNode* root) {
        vector<int> res;
        stack<TreeNode*> nodes;
        do {
            downtoLeaf(root, nodes);
            root = nullptr;
            while (!nodes.empty() && !root) {
                root = nodes.top();
                nodes.pop();
                if (!res.empty() && root->val <= res.back()) {
                    return false;
                }
                res.push_back(root->val);
                root = nodes.top();
                nodes.pop();
            }
        } while (root);
        return true;
    }
    
public:
    bool isValidBST(TreeNode* root) {
        return validInorderTraversal(root);
    }
};
