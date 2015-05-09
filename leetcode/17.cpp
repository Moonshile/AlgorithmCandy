class Solution {
private:
    struct Node {
        const char *c;
        int accessed;
        Node(const char *ch): c(ch), accessed(0) {}
    };
    vector<Node> mapper{" ", "", "abc", "def", "ghi", "jkl", "mno", "pqrs", "tuv", "wxyz"};
public:
    vector<string> letterCombinations(string digits) {
        vector<Node> graph;
        for (auto d: digits) {
            graph.push_back(mapper[d - '0']);
        }
        char *tmp = (char*)malloc(sizeof(char)*(graph.size() + 1));
        tmp[graph.size()] = '\0';
        vector<string> res;
        int level = 0;
        while (digits.size() && level >= 0) {
            // forwarding
            while (level < graph.size()) {
                tmp[level] = graph[level].c[graph[level].accessed++];
                ++level;
            }
            res.push_back(tmp);
            // backtracking
            while (--level >= 0 && graph[level].accessed == strlen(graph[level].c)) {
                graph[level].accessed = 0;
            }
        }
        return res;
    }
};