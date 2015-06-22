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
    ListNode *reverseList(ListNode *first, ListNode *&last) {
        if (first != last) {
            ListNode *new_first = reverseList(first->next, last);
            first->next = last->next;
            last->next = first;
            last = first;
            return new_first;
        }
        return first;
    }
    
public:
    ListNode *reverseList(ListNode *head) {
        ListNode *last = head;
        while (last && last->next) {
            last = last->next;
        }
        return reverseList(head, last);
    }
};
