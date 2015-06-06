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
    TreeNode* insert(TreeNode *origin, TreeNode *to_ins) {
        if (!origin) {
            return to_ins;
        } else if (to_ins) {
            TreeNode *parent, *tmp = origin;
            while (tmp) {
                parent = tmp;
                tmp = tmp->val > to_ins->val ? tmp->left : tmp->right;
            }
            parent->val > to_ins->val ? parent->left = to_ins : parent->right = to_ins;
        }
        return origin;
    }
    
    TreeNode* copyInc(TreeNode *origin, int inc) {
        if (origin) {
            TreeNode *res = new TreeNode(origin->val + inc);
            res->left = copyInc(origin->left, inc);
            res->right = copyInc(origin->right, inc);
            return res;
        }
        return nullptr;
    }
    
    void freeTree(TreeNode *origin) {
        if (origin) {
            freeTree(origin->left);
            freeTree(origin->right);
            delete origin;
        }
    }
    
public:
    vector<TreeNode*> generateTrees(int n) {
        TreeNode *one = new TreeNode(1);
        vector<TreeNode*> none{nullptr}, ones{one};
        vector<vector<TreeNode*>> res{none, ones};
        for (int i = 2; i <= n; ++i) {
            vector<TreeNode*> tmp;
            for (int j = 0; j < (i + 1)>>1; ++j) {
                TreeNode node(i);
                for (auto t: res[j]) {
                    TreeNode *top = insert(copyInc(t, 0), copyInc(&node, 0));
                    for (auto u: res[i - 1 - j]) {
                        tmp.push_back(insert(copyInc(top, 0), copyInc(u, j)));
                    }
                    freeTree(top);
                }
                if (j == i - 1 - j) {
                    continue;
                }
                for (auto t: res[i - 1 - j]) {
                    TreeNode *top = insert(copyInc(t, 0), copyInc(&node, 0));
                    for (auto u: res[j]) {
                        tmp.push_back(insert(copyInc(top, 0), copyInc(u, i - 1 - j)));
                    }
                    freeTree(top);
                }
            }
            res.push_back(tmp);
        }
        for (int i = 0; i < n; ++i) {
            for (auto t: res[i]) {
                freeTree(t);
            }
        }
        return res[n];
    }
};
