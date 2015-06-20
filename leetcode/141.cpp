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
    bool hasCycle(ListNode *head) {
        ListNode *fast = head && head->next ? head->next->next : nullptr;
        ListNode *slow = head ? head->next : nullptr;
        while (fast && fast != slow) {
            slow = slow->next;
            fast = fast->next ? fast->next->next : nullptr;
        }
        return fast != nullptr;
    }
};