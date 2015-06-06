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
    ListNode* reverseBetween(ListNode* head, int m, int n) {
        ListNode dummy(0), *pre = &dummy, *pi = head, *pj, *tmp;
        dummy.next = head;
        for (int i = 1; i < m; ++i) {
            pre = pi;
            pi = pi->next;
        }
        pj = pi->next;
        for (int i = 0; i < n - m; ++i) {
            tmp = pj->next;
            pj->next = pi;
            pi = pj;
            pj = tmp;
        }
        pre->next->next = pj;
        pre->next = pi;
        return dummy.next;
    }
};
