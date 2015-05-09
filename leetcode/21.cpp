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
    ListNode* mergeTwoLists(ListNode* l1, ListNode* l2) {
        if (!l1 || !l2) {
            return l1 ? l1 : l2;
        }
        // cur always is the lower one; find the first element greater than gt; exchange gt and cur
        ListNode *cur = l1->val < l2->val ? l1 : l2, *gt = l1->val < l2->val ? l2 : l1, *res = cur, *old_gt;
        while (cur && gt) {
            for(; cur->next && cur->next->val <= gt->val; cur = cur->next);
            old_gt = gt;
            gt = cur->next;
            cur->next = old_gt;
            cur = old_gt;
        }
        return res;
    }
};