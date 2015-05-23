class Solution {
public:
    int minDistance(string word1, string word2) {
        if (word1.size() == 0 || word2.size() == 0) {
            return word1.size() + word2.size();
        }
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
};
