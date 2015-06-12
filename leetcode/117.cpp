/**
 * Definition for binary tree with next pointer.
 * struct TreeLinkNode {
 *  int val;
 *  TreeLinkNode *left, *right, *next;
 *  TreeLinkNode(int x) : val(x), left(NULL), right(NULL), next(NULL) {}
 * };
 */
class Solution {
private:
    inline void connectIfExists(TreeLinkNode *&back, TreeLinkNode *node) {
        if (node) {
            back->next = node;
            back = node;
        }
    }
    
public:
    void connect(TreeLinkNode *root) {
        if (root) {
            TreeLinkNode *q_front = root, *q_back = root;
            while (q_front) {
                connectIfExists(q_back, q_front->left);
                connectIfExists(q_back, q_front->right);
                q_front = q_front->next;
            }
            TreeLinkNode *next = root, *pre;
            do {
                for (pre = next->next; pre && !pre->left && !pre->right; pre = pre->next) {}
                next->next = nullptr;
                for (next = pre; next && next->next != pre->left && next->next != pre->right; next = next->next) {}
            } while (pre);
        }
    }
};
