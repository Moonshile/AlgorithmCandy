class Solution {
public:
    vector<string> generateParenthesis(int n) {
        int open = n, close = n, index = 0;
        char *tmp = (char*)malloc(sizeof(char)*(2*n + 1));
        tmp[2*n] = '\0';
        vector<string> res;
        while (n && tmp[0] != ')') {
            // forwarding: use up all parentheses
            for (; open > 0; --open, tmp[index++] = '(');
            for (; close > 0; --close, tmp[index++] = ')');
            res.push_back(tmp);
            // backtrack to last valid position
            do {
                // search last '(' and replace it with ')'
                for (; tmp[--index] == ')'; ++close);
                tmp[index++] = ')';
                ++open;
                --close;
                // if there are more ')' than '(' then keep backtracking
            } while (close < open && tmp[0] != ')');
        }
        return res;
    }
};