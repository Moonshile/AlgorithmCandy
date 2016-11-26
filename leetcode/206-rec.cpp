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
    ListNode* reverseList(ListNode* head) {
        if( head == nullptr || head->next == nullptr )
        {
            return head;
        }
        
        ListNode* tail = reverseList( head->next );
        ListNode* last = tail;
        while( last->next )
        {
            last = last->next;
        }
        last->next = head;
        head->next = nullptr;
        
        return tail;
    }
};
