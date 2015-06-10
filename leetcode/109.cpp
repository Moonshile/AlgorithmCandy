/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode(int x) : val(x), next(NULL) {}
 * };
 */
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
    TreeNode* build(ListNode *begin, ListNode *end) {
        if (begin == end) {
            return nullptr;
        }
        ListNode *fast = begin, *slow = begin;
        while (fast != end) {
            fast = fast->next;
            if (fast != end) {
                fast = fast->next;
                slow = slow->next;
            }
        }
        TreeNode *node = new TreeNode(slow->val);
        node->left = build(begin, slow);
        node->right = build(slow->next, end);
        return node;
    }
    
public:
    TreeNode* sortedListToBST(ListNode* head) {
        return build(head, nullptr);
    }
};
