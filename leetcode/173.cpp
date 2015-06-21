/**
 * Definition for binary tree
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode(int x) : val(x), left(NULL), right(NULL) {}
 * };
 */
class BSTIterator {
private:
    stack<TreeNode*> s;
    
    void downtoLeaf(TreeNode *root) {
        while (root) {
            s.push(root->right);
            s.push(root);
            root = root->left;
        }
    }
    
public:
    BSTIterator(TreeNode *root): s() {
        downtoLeaf(root);
    }

    /** @return whether we have a next smallest number */
    bool hasNext() {
        return !s.empty();
    }

    /** @return the next smallest number */
    int next() {
        int res = s.top()->val;
        s.pop();
        auto right = s.top();
        s.pop();
        downtoLeaf(right);
        return res;
    }
};

/**
 * Your BSTIterator will be called like this:
 * BSTIterator i = BSTIterator(root);
 * while (i.hasNext()) cout << i.next();
 */
 