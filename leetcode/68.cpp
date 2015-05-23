class Solution {
private:
    string strsToStr(vector<string> &words, int first, int len, int width, int maxWidth) {
        int extraWidth = maxWidth - width;
        int avgBlanks = len == 1 ? max(0, extraWidth) : extraWidth/(len - 1) + 1;
        int extraBlanks = len == 1 ? 0 : extraWidth%(len - 1);
        string baseBlanks(avgBlanks, ' ');
        stringstream ss;
        ss << words[first];
        for (int j = 1; j < len; ++j) {
            ss << baseBlanks;
            if (extraBlanks > 0) {
                ss << ' ';
                --extraBlanks;
            }
            ss << words[first + j];
        }
        if (len == 1) {
            ss << baseBlanks;
        }
        return ss.str();
    }
    
public:
    vector<string> fullJustify(vector<string>& words, int maxWidth) {
        vector<string> res;
        int first = -1, len = 0, width = 0;
        for (int i = 0; i < words.size(); ++i) {
            if (first == -1) {
                first = i;
                width += words[i].size();
            } else {
                width += words[i].size() + 1;
            }
            ++len;
            if (width >= maxWidth) {
                if (len > 1 && width > maxWidth) {
                    --len;
                    width -= words[i].size() + 1;
                    --i;
                }
                res.push_back(strsToStr(words, first, len, width, maxWidth));
                first = -1;
                len = 0;
                width = 0;
            }
        }
        if (len > 0) {
            string s = strsToStr(words, first, len, width, width);
            string blanks(maxWidth - width > 0 ? maxWidth - width : 0, ' ');
            res.push_back(s + blanks);
        }
        return res;
    }
};
