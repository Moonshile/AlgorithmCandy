/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode(int x) : val(x), left(NULL), right(NULL) {}
 * };
 */
 
int myPow(int x, int n) {
    if (x == 0) {
        return 0;
    } else if (n == 0) {
        return 1;
    } else if (n < 0) {
        return 1/myPow(x, -(1 + n))/x;
    } else if (n%2 == 1) {
        int p = myPow(x, (n - 1)>>1);
        return x*p*p;
    } else {
        int p = myPow(x, n>>1);
        return p*p;
    }
}

class FullTreeIterator {

friend const FullTreeIterator operator-(const FullTreeIterator &iter, int diff);
friend const FullTreeIterator operator+(const FullTreeIterator &iter, int diff);

public:
    FullTreeIterator(TreeNode* root): tree(root), rank(0), height(0), end_pos(0) {
        while (root) {
            ++height;
            root = root->left;
        }
        end_pos = myPow(2, height - 1);
    }
    
    FullTreeIterator(): FullTreeIterator(nullptr) {}
    
    FullTreeIterator begin() {
        rank = 0;
        return *this;
    }
    
    FullTreeIterator end() {
        rank = end_pos;
        return *this;
    }
    
    int operator-(const FullTreeIterator &iter) {
        return rank - iter.rank;
    }
    
    FullTreeIterator &operator++() {
        ++rank;
        return *this;
    }
    
    bool operator==(const FullTreeIterator &iter) {
        return tree == iter.tree && rank == iter.rank;
    }
    
    bool operator!=(const FullTreeIterator &iter) {
        return tree != iter.tree || rank != iter.rank;
    }
    
    TreeNode *get() {
        if (rank >= end_pos || rank < 0) {
            return nullptr;
        }
        int tmp = rank;
        auto res = tree;
        for (int h = height - 2; h >= 0; --h) {
            res = (tmp & (1 << h)) == 0 ? res->left : res->right;
        }
        return res;
    }
    
    int getRank() {
        return rank;
    }
    
    int getHeight() {
        return height;
    }

private:
    TreeNode *tree;
    int rank;
    int height;
    int end_pos;
};

    
const FullTreeIterator operator-(const FullTreeIterator &iter, int diff) {
    FullTreeIterator res = iter;
    res.rank -= diff;
    return res;
}

const FullTreeIterator operator+(const FullTreeIterator &iter, int diff) {
    FullTreeIterator res = iter;
    res.rank += diff;
    return res;
}

class Solution {
public:
    int countNodes(TreeNode* root) {
        FullTreeIterator iter(root), begin = iter.begin(), end = iter.end(), middle;
        int len = end - begin, half;
        while (len > 0) {
            half = len >> 1;
            middle = begin + half;
            if (middle.get() == nullptr) {
                len = half;
            } else {
                begin = middle + 1;
                len = len - half - 1;
            }
        }
        return begin.getHeight() == 0 ? 0 : myPow(2, begin.getHeight() - 1) - 1 + begin.getRank();
    }
};
