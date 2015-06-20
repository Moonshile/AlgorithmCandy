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
    ListNode *mergeTwoLists(ListNode* l1, ListNode* l2) {
        if (!l1 || !l2) {
            return l1 ? l1 : l2;
        }
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
    
    // return number of sorted parts after this merge
    int mergeInK(ListNode *dummied_head, int k) {
        ListNode *pre = dummied_head, *first = pre->next, *second = first, *next_first;
        int res = 0;
        while (first) {
            for (int i = 0; i < k - 1 && second; ++i) {
                second = second->next;
            }
            if (second && second->next) {
                auto tmp = second->next;
                second->next = nullptr;
                second = tmp;
                for (int i = 0; i < k - 1 && tmp; ++i) {
                    tmp = tmp->next;
                }
                if (tmp) {
                    next_first = tmp->next;
                    tmp->next = nullptr;
                } else {
                    next_first = nullptr;
                }
                pre->next = mergeTwoLists(first, second);
                while (pre->next) {
                    pre = pre->next;
                }
                second = first = next_first;
            } else {
                pre->next = first;
                first = nullptr;
            }
            ++res;
        }
        return res;
    }
    
public:
    ListNode *sortList(ListNode *head) {
        ListNode dummy(0);
        dummy.next = head;
        int i = INT_MAX, j = 1;
        while (i > 1) {
            i = mergeInK(&dummy, j);
            j <<= 1;
        }
        return dummy.next;
    }
};
