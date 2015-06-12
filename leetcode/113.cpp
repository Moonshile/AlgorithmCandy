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
    void findPath(TreeNode* root, int sum, vector<int> path, vector<vector<int>> &res) {
        if (root) {
            path.push_back(root->val);
            if (root->left) {
                findPath(root->left, sum - root->val, path, res);
            }
            if (root->right) {
                findPath(root->right, sum - root->val, path, res);
            }
            if (!root->left && !root->right && sum == root->val) {
                res.push_back(path);
            }
        }
    }
    
public:
    vector<vector<int>> pathSum(TreeNode* root, int sum) {
        vector<vector<int>> res;
        vector<int> path;
        findPath(root, sum, path, res);
        return res;
    }
};
