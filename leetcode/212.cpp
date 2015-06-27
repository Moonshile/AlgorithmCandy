class TrieNode {
    friend class Trie;
public:
    // Initialize your data structure here.
    TrieNode(char charactor): c(charactor), word_end(false) {
        for (auto &c: children) {
            c = nullptr;
        }
    }
    
    TrieNode(): TrieNode('.') {}
    
    ~TrieNode() {
        for (auto &c: children) {
            if (c) {
                delete c;
                c = nullptr;
            }
        }
    }
    
private:
    char c;
    bool word_end;
    TrieNode *children[26];
};

class Trie {
public:
    Trie(): root() {}

    // Inserts a word into the trie.
    void insert(string &word) {
        TrieNode *parent = &root;
        for (char c: word) {
            if (parent->children[c - 'a'] == nullptr) {
                auto ptr = new TrieNode(c);
                parent->children[c - 'a'] = ptr;
            }
            parent = parent->children[c - 'a'];
        }
        parent->word_end = true;
    }

    // Returns if the word is in the trie.
    bool search(string &word) {
        TrieNode *parent = &root;
        for (char c: word) {
            if (parent->children[c - 'a'] == nullptr) {
                return false;
            }
            parent = parent->children[c - 'a'];
        }
        bool res = parent->word_end;
        // this line is just for this problem to prevent a same word to be added more than twice
        parent->word_end = false;
        return res;
    }

    // Returns if there is any word in the trie
    // that starts with the given prefix.
    bool startsWith(string &prefix) {
        TrieNode *parent = &root;
        for (char c: prefix) {
            if (parent->children[c - 'a'] == nullptr) {
                return false;
            }
            parent = parent->children[c - 'a'];
        }
        return true;
    }

private:
    TrieNode root;
};

class Solution {
private:
    inline vector<pair<int, int>> sequence(int i, int j) {
        return vector<pair<int, int>>{
            pair<int, int>({i - 1, j}), 
            pair<int, int>({i + 1, j}), 
            pair<int, int>({i, j - 1}), 
            pair<int, int>({i, j + 1})
        };
    }

    void dfs(vector<vector<char>> &board, int i, int j, int m, int n, string cur, vector<string> &res, Trie &trie) {
        cur = cur + board[i][j];
        if (trie.startsWith(cur)) {
            board[i][j] = '\0';
            auto sequences = sequence(i, j);
            for (auto &p: sequences) {
                int &ii = p.first, &jj = p.second;
                if (ii >= 0 && ii < m && jj >= 0 && jj < n && board[ii][jj]) {
                    dfs(board, ii, jj, m, n, cur, res, trie);
                }
            }
            board[i][j] = cur.back();
            if (trie.search(cur)) {
                res.push_back(cur);
            }
        }
    }

public:
    vector<string> findWords(vector<vector<char>> &board, vector<string>& words) {
        unordered_set<char> chars;
        for (auto &line: board) {
            for (char c: line) {
                chars.insert(c);
            }
        }
        Trie trie;
        for (auto &w: words) {
            bool clean = true;
            for (auto c: w) {
                if (chars.count(c) == 0) {
                    clean = false;
                    break;
                }
            }
            if (clean) {
                trie.insert(w);
            }
        }
        vector<string> res;
        for (int i = 0, m = board.size(); i < m; ++i) {
            for (int j = 0, n = board[i].size(); j < n; ++j) {
                dfs(board, i, j, m, n, "", res, trie);
            }
        }
        return res;
    }
};
