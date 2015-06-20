/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode(int x) : val(x), next(NULL) {}
 * };
 */
class Solution {
private:
    void insertAfter(ListNode *base, ListNode *node) {
        node->next = base->next;
        base->next = node;
    }
    
    ListNode *lowerBound(ListNode *dummied_head, int val) {
        ListNode *pre = dummied_head, *i = pre->next;
        while (i && i->val <= val) {
            pre = i;
            i = i->next;
        }
        return pre;
    }
    
public:
    ListNode *insertionSortList(ListNode *head) {
        ListNode dummy(0), *cur = head;
        while (cur) {
            auto tmp = cur;
            cur = cur->next;
            tmp->next = nullptr;
            insertAfter(lowerBound(&dummy, tmp->val), tmp);
        }
        return dummy.next;
    }
};