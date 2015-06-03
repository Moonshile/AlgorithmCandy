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
        ListNode* i = head, *j = head ? head->next : nullptr, *tmp;
        while (j) {
            while (j && j->val == i->val) {
                tmp = j;
                j = j->next;
                delete tmp;
            }
            i->next = j;
            i = j;
            j = j ? j->next : nullptr;
        }
        return head;
    }
};
