// karp-rabin's algorithm
class Solution {
    bool strcmp(const string &haystack, const string &needle, const int index) {
        int i;
        for(i = 0; i < needle.size(); ++i) {
            if (haystack[i + index] != needle[i]) {
                break;
            }
        }
        return i == needle.size();
    }
public:
    int strStr(string haystack, string needle) {
        unsigned long long source = 0, target = 0, ones = 0ULL - 1, size = needle.size(), bits = (size - 1)*8;
        for (int i = 0; i < haystack.size(); ++i) {
            if (i < size) {
                source = source << 8 | haystack[i];
                target = target << 8 | needle[i];
            } else {
                source = size > 8 ? source << 8 | haystack[i] : (~(ones << bits) & source) << 8 | haystack[i];
            }
            if (i >= size - 1 && source == target && strcmp(haystack, needle, i - size + 1)) {
                return i - size + 1;
            }
        }
        return size == 0 ? 0 : -1;
    }
};
