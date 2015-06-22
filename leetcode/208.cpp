class TrieNode {
    friend class Trie;
public:
    // Initialize your data structure here.
    TrieNode(char charactor): c(charactor), word_end(false), children() {}
    TrieNode(): TrieNode('.') {}
private:
    char c;
    bool word_end;
    unordered_map<char, shared_ptr<TrieNode>> children;
};

class Trie {
public:
    Trie(): root(new TrieNode()) {}

    // Inserts a word into the trie.
    void insert(string &word) {
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

    // Returns if the word is in the trie.
    bool search(string &word) {
        TrieNode *parent = root.get();
        for (char c: word) {
            if (parent->children.count(c) == 0) {
                return false;
            }
            parent = parent->children[c].get();
        }
        return parent->word_end;
    }

    // Returns if there is any word in the trie
    // that starts with the given prefix.
    bool startsWith(string &prefix) {
        TrieNode *parent = root.get();
        for (char c: prefix) {
            if (parent->children.count(c) == 0) {
                return false;
            }
            parent = parent->children[c].get();
        }
        return true;
    }

private:
    shared_ptr<TrieNode> root;
};

// Your Trie object will be instantiated and called as such:
// Trie trie;
// trie.insert("somestring");
// trie.search("key");
