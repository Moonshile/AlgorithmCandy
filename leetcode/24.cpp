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
    ListNode* swapPairs(ListNode* head) {
        ListNode *i = head, *j = head ? head->next : head, *pre_i = i;
        while (i && j) {
            i->next = j->next;
            j->next = i;
            i == head ? head = j : pre_i->next = j;
            pre_i = i;
            i = i->next;
            j = i ? i->next : i;
        }
        return head;
    }
};