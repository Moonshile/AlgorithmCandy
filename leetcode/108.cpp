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
    
    TreeNode* convert(citer begin, citer end) {
        if (begin == end) {
            return nullptr;
        }
        auto len = end - begin, half = len >> 1;
        TreeNode *node = new TreeNode(*(begin + half));
        node->left = convert(begin, begin + half);
        node->right = convert(begin + half + 1, end);
        return node;
    }
    
public:
    TreeNode* sortedArrayToBST(vector<int>& nums) {
        return convert(nums.begin(), nums.end());
    }
};
