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
    
    TreeNode* build(citer in_begin, citer in_end, citer post_begin, citer post_end) {
        if (post_begin == post_end) {
            return nullptr;
        }
        auto t = post_end - 1, p = in_begin;
        while (*p != *t) {
            ++p;
        }
        TreeNode *node = new TreeNode(*t);
        node->left = build(in_begin, p, post_begin, post_begin + (p - in_begin));
        node->right = build(p + 1, in_end, post_begin + (p - in_begin), post_end - 1);
        return node;
    }
    
public:
    TreeNode* buildTree(vector<int>& inorder, vector<int>& postorder) {
        return build(inorder.begin(), inorder.end(), postorder.begin(), postorder.end());
    }
};
