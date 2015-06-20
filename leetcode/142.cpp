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
    ListNode *detectCycle(ListNode *head) {
        ListNode *fast = head && head->next ? head->next->next : nullptr;
        ListNode *slow = head ? head->next : nullptr;
        while (fast && fast != slow) {
            slow = slow->next;
            fast = fast->next ? fast->next->next : nullptr;
        }
        if (fast == nullptr) {
            return nullptr;
        }
        fast = head;
        while (fast != slow) {
            fast = fast->next;
            slow = slow->next;
        }
        return fast;
    }
};
