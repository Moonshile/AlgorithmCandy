/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode(int x) : val(x), next(NULL) {}
 * };
 */
class Solution {
public:
    void deleteNode(ListNode* node) {
        if (node && node->next) {
            auto tmp = node->next;
            node->val = tmp->val;
            node->next = tmp->next;
            delete tmp;
        }
    }
};
