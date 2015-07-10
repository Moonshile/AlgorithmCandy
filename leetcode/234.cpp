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
    bool isPalindrome(ListNode* head) {
        if (head) {
            ListNode *slow = head, *fast = head && head->next ? head->next->next : nullptr;
            while (fast) {
                slow = slow->next;
                fast = fast->next;
                if (fast) {
                    fast = fast->next;
                }
            }
            ListNode *tmp = reverseList(slow->next, nullptr), *p1 = head, *p2 = tmp;
            slow->next = nullptr;
            while (p2 && p2->val == p1->val) {
                p2 = p2->next;
                p1 = p1->next;
            }
            slow->next = reverseList(tmp, nullptr);
            return p2 == nullptr;
        }
        return true;
    }
};
