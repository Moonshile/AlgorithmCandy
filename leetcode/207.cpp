
struct TopNode {
    int val;
    int indeg;
    vector<int> children;
    TopNode(int v): val(v), indeg(0), children() {}
    TopNode(): TopNode(0) {}
};

class TopGraph {
private:
    unordered_map<int, TopNode> g;
    
public:
    TopGraph(): g() {}
    
    void addEdge(int from, int to) {
        if (g.count(from) == 0) {
            g.emplace(from, from);
        }
        if (g.count(to) == 0) {
            g.emplace(to, to);
        }
        g[from].children.push_back(to);
        ++g[to].indeg;
    }
    
    void removeNode(int from) {
        if (g.count(from) > 0) {
            for (auto to: g[from].children) {
                --g[to].indeg;
            }
            g.erase(from);
        }
    }
    
    bool empty() {
        return g.empty();
    }
    
    TopNode *nextZeroIndeg() {
        for (auto it = g.begin(); it != g.end(); ++it) {
            if (it->second.indeg == 0) {
                return &it->second;
            }
        }
        return nullptr;
    }
    
    vector<TopNode> topSort() {
        auto tmp = *this;
        vector<TopNode> res;
        auto next = tmp.nextZeroIndeg();
        while (next) {
            res.push_back(g[next->val]);
            tmp.removeNode(next->val);
            next = tmp.nextZeroIndeg();
        }
        return tmp.empty() ? res : vector<TopNode>();
    }
};

class Solution {
public:
    bool canFinish(int numCourses, vector<pair<int, int>> &prerequisites) {
        TopGraph tg;
        for (auto &p: prerequisites) {
            tg.addEdge(p.second, p.first);
        }
        return !tg.topSort().empty() || prerequisites.empty();
    }
};
