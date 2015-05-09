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
    ListNode* removeNthFromEnd(ListNode* head, int n) {
        // p2 moves to nth, then p1/p2 moves together until p2 arrives the last element
        ListNode *p1 = head, *p2 = head;
        for (int i = 0; i < n; ++i, p2 = p2->next);
        if (!p2) {
            return p1->next;
        }
        for (; p2->next; p1 = p1->next, p2 = p2->next);
        p1->next = p1->next->next;
        return head;
    }
};