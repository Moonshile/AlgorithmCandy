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
    ListNode* deleteDuplicates(ListNode* head) {
        ListNode dummy(0), *pre = &dummy, *i = head, *j = i, *tmp;
        dummy.next = head;
        while (j) {
            while (j && j->val == i->val) {
                j = j->next;
            }
            if (i && i -> next == j) {
                pre = i;
                i = j;
            } else if (i) {
                pre->next = j;
                while (i != j) {
                    tmp = i;
                    i = i -> next;
                    delete tmp;
                }
            }
        }
        return dummy.next;
    }
};
