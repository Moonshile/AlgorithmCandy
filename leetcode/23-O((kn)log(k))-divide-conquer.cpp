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
    ListNode* mergeTwoLists(ListNode* l1, ListNode* l2) {
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
    ListNode* mergeK(vector<ListNode*>::const_iterator begin, vector<ListNode*>::const_iterator end) {
        if (begin == end) {
            return nullptr;
        } else if (end - begin == 1) {
            return *begin;
        } else if (end - begin == 2) {
            return mergeTwoLists(*begin, *(begin + 1));
        }
        vector<ListNode*>::const_iterator mid = begin + (end - begin)/2;
        return mergeTwoLists(mergeK(begin, mid), mergeK(mid, end));
    }
public:
    ListNode* mergeKLists(vector<ListNode*>& lists) {
        return mergeK(lists.begin(), lists.end());
    }
};