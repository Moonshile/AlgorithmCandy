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
    ListNode *getIntersectionNode(ListNode *headA, ListNode *headB) {
        int lenA = 1, lenB = 1;
        ListNode *pa = headA, *pb = headB;
        while (pa && pa->next) {
            pa = pa->next;
            ++lenA;
        }
        while (pb && pb->next) {
            pb = pb->next;
            ++lenB;
        }
        if (!(pa && pa == pb)) {
            return nullptr;
        }
        int diff = abs(lenA - lenB);
        ListNode *longer = lenA > lenB ? headA : headB, *shorter = lenA > lenB ? headB : headA;
        for (int i = 0; i < diff; ++i) {
            longer = longer->next;
        }
        while (longer != shorter) {
            longer = longer->next;
            shorter = shorter->next;
        }
        return longer;
    }
};
