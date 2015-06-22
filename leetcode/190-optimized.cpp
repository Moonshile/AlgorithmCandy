class Solution {
private:
    vector<uint32_t> lib;
    
    uint32_t revBits(uint8_t n) {
        uint32_t res = 0;
        for (int i = 0; i < 8; ++i) {
            res = (res << 1) | ((n >> i)&1);
        }
        return res;
    }
    
public:
    Solution(): lib() {
        lib.push_back(0);
        for (uint8_t i = 1; i > 0; ++i) {
            lib.push_back(revBits(i));
        }
    }

    uint32_t reverseBits(uint32_t n) {
        uint32_t res = 0;
        for (int i = 0; i < 32; i += 8) {
            res = (res << 8) | lib[(n >> i)&0xFFU];
        }
        return res;
    }
};
