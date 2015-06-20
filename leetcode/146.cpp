struct CacheNode {
    int key;
    int val;
    CacheNode *pre;
    CacheNode *next;
    CacheNode(int k, int v): key(k), val(v), pre(nullptr), next(nullptr) {}
    
    void insertAfter(CacheNode *node) {
        node->next = this->next;
        node->pre = this;
        this->next->pre = node;
        this->next = node;
    }
    
    void remove() {
        this->pre->next = this->next;
        this->next->pre = this->pre;
    }
};

class LRUCache{
private:
    CacheNode *head, *tail;
    unordered_map<int, CacheNode*> cache;
    int size;
    int capacity;
    
public:
    LRUCache(int c): head(new CacheNode(0, 0)), tail(new CacheNode(0, 0)), cache(), size(0), capacity(c) {
        head->next = tail;
        tail->pre = head;
    }
    
    ~LRUCache() {
        CacheNode *tmp = head, *to_del;
        while (tmp) {
            to_del = tmp;
            tmp = tmp->next;
            delete to_del;
        }
    }
    
    int get(int key) {
        if (cache.count(key) > 0) {
            auto cur = cache[key];
            cur->remove();
            head->insertAfter(cur);
            return cur->val;
        }
        return -1;
    }
    
    void set(int key, int value) {
        CacheNode *node = nullptr;
        if (cache.count(key) > 0) {
            node = cache[key];
            node->val = value;
            node->remove();
        } else if (size == capacity) {
            node = tail->pre;
            node->remove();
            cache.erase(node->key);
            node->key = key;
            node->val = value;
        } else {
            node = new CacheNode(key, value);
            ++size;
        }
        head->insertAfter(node);
        cache[key] = node;
    }
};
