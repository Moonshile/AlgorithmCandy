class Solution {
public:
    int computeArea(int A, int B, int C, int D, int E, int F, int G, int H) {
        int a1 = (D - B)*(C - A), a2 = (H - F)*(G - E);
        int hr = min(C, G), hl = max(A, E), vt = min(D, H), vb = max(B, F);
        return a1 - (hr > hl ? hr - hl : 0)*(vt > vb ? vt - vb : 0) + a2;
    }
};
