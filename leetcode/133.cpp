/**
 * Definition for undirected graph.
 * struct UndirectedGraphNode {
 *     int label;
 *     vector<UndirectedGraphNode *> neighbors;
 *     UndirectedGraphNode(int x) : label(x) {};
 * };
 */
class Solution {
public:
    UndirectedGraphNode *cloneGraph(UndirectedGraphNode *node) {
        if (!node) {
            return nullptr;
        }
        // nullptr represents has been cloned
        unordered_map<int, UndirectedGraphNode*> m;
        unordered_set<int> accessed;
        UndirectedGraphNode *res = new UndirectedGraphNode(node->label);
        m[node->label] = res;
        queue<UndirectedGraphNode*> q({node});
        while (!q.empty()) {
            auto cur = q.front();
            q.pop();
            if (accessed.count(cur->label) > 0) {
                continue;
            }
            for (auto n: cur->neighbors) {
                if (m.count(n->label) == 0) {
                    m[n->label] = new UndirectedGraphNode(n->label);
                }
                m[cur->label]->neighbors.push_back(m[n->label]);
                q.push(n);
            }
            accessed.insert(cur->label);
        }
        return res;
    }
};
