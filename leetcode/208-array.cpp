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
        return parent->word_end;
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

// Your Trie object will be instantiated and called as such:
// Trie trie;
// trie.insert("somestring");
// trie.search("key");
