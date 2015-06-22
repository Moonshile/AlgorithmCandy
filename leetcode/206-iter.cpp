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
    ListNode *reverseList(ListNode *begin, ListNode *end) {
        if (begin == end) {
            return begin;
        }
        ListNode *i = begin, *j = i->next, *k = j == end ? nullptr : j->next;
        while (j != end) {
            j -> next = i;
            i = j;
            j = k;
            k = k == end ? nullptr : k->next;
        }
        begin->next = end;
        return i;
    }
    
public:
    ListNode *reverseList(ListNode *head) {
        return reverseList(head, nullptr);
    }
};
