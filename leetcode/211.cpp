class TrieNode {
    friend class WordDictionary;
public:
    // Initialize your data structure here.
    TrieNode(char charactor): c(charactor), word_end(false), children() {}
    TrieNode(): TrieNode('.') {}
private:
    char c;
    bool word_end;
    unordered_map<char, shared_ptr<TrieNode>> children;
};

class WordDictionary {
public:
    WordDictionary(): root(new TrieNode()) {}

    // Adds a word into the data structure.
    void addWord(string word) {
        TrieNode *parent = root.get();
        for (char c: word) {
            if (parent->children.count(c) == 0) {
                auto ptr = shared_ptr<TrieNode>(new TrieNode(c));
                parent->children[c] = ptr;
            }
            parent = parent->children[c].get();
        }
        parent->word_end = true;
    }

    // Returns if the word is in the data structure. A word could
    // contain the dot character '.' to represent any one letter.
    bool search(string word) {
        queue<TrieNode*> q({root.get(), nullptr});
        for (char c: word) {
            if (q.empty()) {
                return false;
            }
            while (q.front() != nullptr) {
                auto node = q.front();
                q.pop();
                if (c == '.') {
                    for (auto c = node->children.begin(); c != node->children.end(); ++c) {
                        q.push(c->second.get());
                    }
                } else if (node->children.count(c) > 0) {
                    q.push(node->children[c].get());
                }
            }
            q.pop();
            if (!q.empty()) {
                q.push(nullptr);
            }
        }
        while (!q.empty() && q.front() != nullptr) {
            auto node = q.front();
            q.pop();
            if (node->word_end) {
                return true;
            }
        }
        return false;
    }

private:
    shared_ptr<TrieNode> root;
};

// Your WordDictionary object will be instantiated and called as such:
// WordDictionary wordDictionary;
// wordDictionary.addWord("word");
// wordDictionary.search("pattern");
