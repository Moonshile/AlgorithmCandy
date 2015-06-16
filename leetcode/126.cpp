// Example program
#include <iostream>
#include <string>
#include <unordered_set>
#include <unordered_map>
#include <memory>
#include <queue>
#include <vector>
#include <algorithm>

using namespace std;
int editDistance(string word1, string word2) {
    vector<int> res(word2.size() + 1, 0), next(word2.size() + 1, 0), *cur_p = &res, *next_p = &next;
    for (int j = 0; j <= word2.size(); ++j) {
        res[j] = j;
    }
    for (int i = 0; i < word1.size(); ++i) {
        for (int j = 0; j <= word2.size(); ++j) {
            if (j == 0) {
                (*next_p)[j] = (*cur_p)[j] + 1;
            } else {
                int f = word1[i] == word2[j - 1] ? 0 : 1;
                (*next_p)[j] = min(min((*cur_p)[j] + 1, (*next_p)[j - 1] + 1), (*cur_p)[j - 1] + f);
            }
        }
        swap(cur_p, next_p);
    }
    return (*cur_p)[word2.size()];
}

class GraphNode {
private:
    string name;
    mutable int val;
    vector<shared_ptr<GraphNode>> neighbors;
public:
    explicit GraphNode(string &n): name(n), val(0), neighbors() {}
    
    void addNeighbor(const shared_ptr<GraphNode> &node) {
        neighbors.push_back(node);
    }
    
    void shortestPath(string &target) const {
        queue<const GraphNode*> q({this});
        const GraphNode *cur = nullptr;
        while (!q.empty() && cur && cur->name != target) {
            cur = q.front();
            q.pop();
            for (auto pGN: cur->neighbors) {
                auto p = pGN.get();
                p->val = min(p->val, cur->val + 1);
                q.push(p);
            }
        }
    }
    
    vector<vector<string>> shortestPathsToSource() const {
        vector<vector<const GraphNode*>> path1{vector<const GraphNode*>{this}}, path2, *cur = &path1, *next = &path2;
        int next_distance = val;
        while (--next_distance >= 0) {
            for (auto &nodes: *cur) {
                for (auto pGN: nodes.back()->neighbors) {
                    if (pGN.get()->val == next_distance) {
                        auto tmp = nodes;
                        tmp.push_back(pGN.get());
                        next->push_back(tmp);
                    }
                }
            }
            swap(cur, next);
        }
        vector<vector<string>> res;
        for (auto &nodes: *cur) {
            vector<string> tmp;
            for (auto node: nodes) {
                tmp.push_back(node->name);
            }
            res.push_back(tmp);
        }
        return res;
    }
};

class Solution {
public:
    vector<vector<string>> findLadders(string start, string end, unordered_set<string> &dict) {
        unordered_map<string, shared_ptr<GraphNode>> nodes;
        vector<string> names;
        for (string w: dict) {
            nodes[w] = shared_ptr<GraphNode>(new GraphNode(w));
            names.push_back(w);
        }
        for (auto it = names.begin(); it != names.end(); ++it) {
            for (auto jt = it + 1; jt != names.end(); ++jt) {
                if (editDistance(*it, *jt) == 1) {
                    nodes[*it].get()->addNeighbor(nodes[*jt]);
                    nodes[*jt].get()->addNeighbor(nodes[*it]);
                }
            }
        }
        nodes[start].get()->shortestPath(end);
        return nodes[end].get()->shortestPathsToSource();
    }
};
int main()
{
    Solution s;
    unordered_set<string> dict{"hot","dot","dog","lot","log"};
    auto res = s.findLadders("hit", "cog", dict);
    for (auto &nodes: res) {
        for (auto s: nodes) {
            cout << s << " ";
        }
        cout << endl;
    }
    cout << res.size();
}

