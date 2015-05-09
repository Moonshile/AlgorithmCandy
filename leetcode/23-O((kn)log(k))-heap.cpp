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
    struct Compare {
        bool operator()(const ListNode *a, const ListNode *b) const {
            return a == nullptr ? true : (b == nullptr ? false : a->val > b->val);
        }
    };
public:
    ListNode* mergeKLists(vector<ListNode*>& lists) {
        priority_queue<ListNode*, vector<ListNode*>, Compare> queue(lists.begin(), lists.end());
        ListNode *res = new ListNode(-1), *cur = res;
        while(!queue.empty() && queue.top()) {
            auto list = queue.top();
            queue.pop();
            cur->next = list;
            cur = cur->next;
            queue.push(list->next);
        }
        return res->next;
    }
};