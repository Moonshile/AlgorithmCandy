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
    using citer = vector<int>::const_iterator;
    
    TreeNode* build(citer pre_begin, citer pre_end, citer in_begin, citer in_end) {
        if (pre_begin == pre_end) {
            return nullptr;
        }
        auto p = in_begin;
        while (*p != *pre_begin) {
            ++p;
        }
        TreeNode *node = new TreeNode(*pre_begin);
        node->left = build(pre_begin + 1, pre_begin + 1 + (p - in_begin), in_begin, p);
        node->right = build(pre_begin + 1 + (p - in_begin), pre_end, p + 1, in_end);
        return node;
    }
    
public:
    TreeNode* buildTree(vector<int>& preorder, vector<int>& inorder) {
        return build(preorder.begin(), preorder.end(), inorder.begin(), inorder.end());
    }
};
