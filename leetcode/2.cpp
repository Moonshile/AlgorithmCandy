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
    ListNode *addTwoNumbers(ListNode *l1, ListNode *l2) {
        ListNode *res, *p1 = l1, *p2 = l2, *pre1, *pre2;
        int carry = 0;
        while(p1 && p2) {
            p1->val += p2->val + carry;
            carry = p1->val / 10;
            p1->val %= 10;
            p2->val = p1->val;
            pre1 = p1;
            pre2 = p2;
            p1 = p1->next;
            p2 = p2->next;
        }
        res = p1 ? l1 : l2;
        pre1 = p1 ? pre1 : pre2;
        p1 = p1 ? p1 : p2;
        while(p1 && carry) {
            p1->val += carry;
            carry = p1->val / 10;
            p1->val %= 10;
            pre1 = p1;
            p1 = p1->next;
        }
        if(carry) {
            ListNode* node = new ListNode(carry);
            pre1->next = node;
        }
        return res;
    }
};