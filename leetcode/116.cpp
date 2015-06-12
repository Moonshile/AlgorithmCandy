/**
 * Definition for binary tree with next pointer.
 * struct TreeLinkNode {
 *  int val;
 *  TreeLinkNode *left, *right, *next;
 *  TreeLinkNode(int x) : val(x), left(NULL), right(NULL), next(NULL) {}
 * };
 */
class Solution {
public:
    void connect(TreeLinkNode *root) {
        if (root && root->left) {
            TreeLinkNode *q_front = root, *q_back = q_front;
            while (q_front && q_front->left) {
                q_back->next = q_front->left;
                q_back->next->next = q_front->right;
                q_back = q_front->right;
                q_front = q_front->next;
            }
            TreeLinkNode *next = root, *pre;
            int i = 2;
            while (next) {
                pre = next;
                for (int j = 0; j < i && next; ++j) {
                    next = next->next;
                }
                pre->next = nullptr;
                i <<= 1;
            }
        }
    }
};
