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
    void reorderList(ListNode *head) {
        ListNode *slow = head ? head->next : nullptr, *fast = slow ? slow->next : nullptr;
        while (fast) {
            slow = slow->next;
            fast = fast->next ? fast->next->next : nullptr;
        }
        ListNode *back = reverseList(slow, nullptr), *front = head;
        while (back) {
            auto tmp = front->next;
            front->next = back;
            front = tmp;
            tmp = back->next;
            back->next = front;
            back = tmp;
        }
        if (front) {
            front->next = nullptr;
        }
    }
};
