class Solution {
private:
    int nextVersionNo(string s, int &begin) {
        if (begin >= s.size()) {
            begin = -1;
            return 0;
        }
        int res = 0;
        while (begin < s.size() && s[begin] != '.') {
            res = res*10 + s[begin++] - '0';
        }
        return res;
    }
    
public:
    int compareVersion(string version1, string version2) {
        int no1, no2, begin1 = 0, begin2 = 0;
        do {
            no1 = nextVersionNo(version1, begin1);
            no2 = nextVersionNo(version2, begin2);
            ++begin1;
            ++begin2;
        } while (no1 == no2 && begin1 > 0 && begin2 > 0);
        return no1 < no2 ? -1 : (no1 == no2 ? 0 : 1);
    }
};
