class Solution {
public:
    bool isScramble(string s1, string s2) {
        vector<vector<vector<bool>>> scramble;
        int n = s1.size();
        for (int k = 0; k < n; ++k) {
            vector<vector<bool>> tmp;
            for (int i = 0; i < n; ++i) {
                vector<bool> t(n, false);
                tmp.push_back(t);
            }
            scramble.push_back(tmp);
        }
        for (int k = 0; k < n; ++k) {
            for (int i = 0; i < n - k; ++i) {
                for (int j = 0; j < n - k; ++j) {
                    if (k == 0) {
                        scramble[k][i][j] = s1[i] == s2[j];
                    } else {
                        for (int w = 0; w < k; ++w) {
                            if (scramble[w][i][j] && scramble[k - w - 1][i + w + 1][j + w + 1]
                             || scramble[w][i][j + k - w] && scramble[k - w - 1][i + w + 1][j]) {
                                scramble[k][i][j] = true;
                                break;
                            }
                        }
                    }
                }
            }
        }
        return scramble[n - 1][0][0];
    }
};
