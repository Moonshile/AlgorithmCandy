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
    void determine(TreeNode *pre, TreeNode *next, TreeNode *&f1, TreeNode *&f2) {
        if (pre && next && pre->val > next->val) {
            f1 = f1 ? f1 : pre;
            f2 = next;
        }
    }
    
    void downtoLeaf(TreeNode *root, stack<TreeNode*> &s) {
        while (root) {
            s.push(root->right);
            s.push(root);
            root = root->left;
        }
    }
    
    void inorder(TreeNode *root, TreeNode *&f1, TreeNode *&f2) {
        stack<TreeNode*> nodes;
        TreeNode *pre = nullptr;
        do {
            downtoLeaf(root, nodes);
            root = nullptr;
            while (!nodes.empty() && !root) {
                auto next = nodes.top();
                nodes.pop();
                determine(pre, next, f1, f2);
                pre = next;
                root = nodes.top();
                nodes.pop();
            }
        } while (root);
    }
    
public:
    void recoverTree(TreeNode* root) {
        TreeNode *f1 = nullptr, *f2 = nullptr;
        inorder(root, f1, f2);
        if (f1 && f2) {
            swap(f1->val, f2->val);
        }
    }
};
