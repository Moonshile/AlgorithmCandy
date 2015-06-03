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
    ListNode* partition(ListNode* head, int x) {
        ListNode lower(0), not_lower(0), *lp = &lower, *nlp = &not_lower;
        while (head) {
            if (head->val < x) {
                lp->next = head;
                lp = head;
            } else {
                nlp->next = head;
                nlp = head;
            }
            head = head->next;
        }
        nlp->next = nullptr;
        lp->next = not_lower.next;
        return lower.next;
    }
};
