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
    ListNode* reverse(ListNode* head, ListNode *tail) {
        if (head->next != tail) {
            ListNode *i = head, *j = head->next, *k = j->next;
            i->next = tail;
            do {
                j->next = i;
                i = j;
                j = k;
                k = k == tail ? k : k->next;
            } while (j != tail);
            return i;
        }
        return head;
    }
public:
    ListNode* reverseKGroup(ListNode* head, int k) {
        ListNode *res = new ListNode(-1);
        res->next = head;
        ListNode *pre = res, *to_reverse = res->next, *tail = to_reverse;
        do {
            int len;
            for (len = 0; len < k && tail; ++len, tail = tail->next);
            if (len == k) {
                pre->next = reverse(to_reverse, tail);
                for (int i = 0; i < k; ++i, pre = pre->next);
                to_reverse = tail;
                tail = to_reverse;
            } else {
                break;
            }
        } while (true);
        return res->next;
    }
};