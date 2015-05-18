class Solution {
public:
    string countAndSay(int n) {
        string pre("1");
        stringstream next;
        while(n-- > 1) {
            char c = pre[0];
            int count = 0;
            for (int i = 0; i < pre.size(); ) {
                for (; i < pre.size() && c == pre[i]; ++i, ++count) {}
                next << count << c;
                count = 0;
                c = i < pre.size() ? pre[i] : c;
            }
            pre = next.str();
            next.str("");
        }
        return pre;
    }
};
