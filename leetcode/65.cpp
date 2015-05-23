class Solution {
private:
    using sciter = string::const_iterator;
    using siter = string::iterator;
    
    // e[+-]{0,1}\d+
    bool expStart(sciter begin, sciter end) {
        ++begin;
        if (isdigit(*begin)) { // \d+
            while (isdigit(*begin)) {
                ++begin;
            }
            if (begin == end) {
                return true; // e\d+
            }
        } else if (*begin == '+' || *begin == '-') { // [+-]\d+
            ++begin;
            if (isdigit(*begin)) { // \d+
                while (isdigit(*begin)) {
                    ++begin;
                }
                if (begin == end) {
                    return true; // e[+-]\d+
                }
            }
        }
        return false;
    }
    
    // \.\d+(e[+-]{0,1}\d+){0,1}
    bool dotStart(sciter begin, sciter end) {
        ++begin;
        if (isdigit(*begin)) { // \d+(e[+-]{0,1}\d+){0,1}
            while (isdigit(*begin)) {
                ++begin;
            }
            if (begin == end) {
                return true; // \.\d+
            }
            if (*begin == 'e') {
                return expStart(begin, end); // e[+-]{0,1}\d+
            }
        }
        return false;
    }
    
    // \d+(\.(\d+){0,1}){0,1}(e[+-]{0,1}\d+){0,1}
    bool digitStart(sciter begin, sciter end) {
        while (isdigit(*begin)) {
            ++begin;
        }
        if (begin == end) {
            return true; // \d+
        } else if (*begin == '.') {
            ++begin;
            if (begin == end) {
                return true; // \d+\.
            } else if (isdigit(*begin)) { // \d+(e[+-]{0,1}\d+){0,1}
                while (isdigit(*begin)) {
                    ++begin;
                }
                if (begin == end) {
                    return true; // \d+\.\d+
                } else if (*begin == 'e') {
                    return expStart(begin, end); // \d+\.\d+e[+-]{0,1}\d+
                }
            } else if (*begin == 'e') {
                return expStart(begin, end); // \d+\.e[+-]{0,1}\d+
            }
        } else if (*begin == 'e') {
            return expStart(begin, end); // \d+e[+-]{0,1}\d+
        }
        return false;
    }
    
    bool numberStart(sciter begin, sciter end) {
        if (begin != end) {
            if (*begin == '+' || *begin == '-') {
                while(*begin == '+' || *begin == '-') {
                    ++begin;
                }
            }
            if (isdigit(*begin)) {
                return digitStart(begin, end);
            } else if (*begin == '.') {
                return dotStart(begin, end);
            }
        }
        return false;
    }
    
    void preprocess(siter &begin, siter &end) {
        for (; begin != end && isblank(*begin); ++begin) {}
        for (; end != begin && isblank(*(end - 1)); --end) {}
    }
    
public:
    bool isNumber(string s) {
        auto begin = s.begin(), end = s.end();
        preprocess(begin, end);
        return numberStart(begin, end);
    }
};
