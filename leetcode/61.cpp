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
    ListNode* rotateRight(ListNode* head, int k) {
        if (head == nullptr || head->next == nullptr) {
            return head;
        }
        int count = 1;
        ListNode* res = head, *end = head;
        for (; end->next != nullptr; end = end->next, ++count) {}
        k %= count;
        if (k > 0) {
            end->next = head;
            for (int i = 0; i < count - 1 - k; ++i, res = res->next) {}
            ListNode* tmp = res;
            res = res->next;
            tmp->next = nullptr;
        }
        return res;
    }
};
