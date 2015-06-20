/**
 * Definition for singly-linked list with a random pointer.
 * struct RandomListNode {
 *     int label;
 *     RandomListNode *next, *random;
 *     RandomListNode(int x) : label(x), next(NULL), random(NULL) {}
 * };
 */
class Solution {
public:
    RandomListNode *copyRandomList(RandomListNode *head) {
        if (!head) {
            return nullptr;
        }
        auto raw = head;
        while (raw) {
            auto n = new RandomListNode(raw->label);
            n->random = raw->random;
            n->next = raw->next;
            auto raw_next = raw->next;
            raw->next = n;
            raw = raw_next;
        }
        raw = head;
        while (raw) {
            raw->next->random = raw->random ? raw->random->next : nullptr;
            raw = raw->next->next;
        }
        raw = head;
        auto res = raw->next;
        while (raw) {
            auto raw_next = raw->next->next;
            raw->next->next = raw_next ? raw_next->next : nullptr;
            raw->next = raw_next;
            raw = raw_next;
        }
        return res;
    }
};
