// Cho ma tran M dem so ma tran x sao cho Mx = O (ma tran 0)
// so ma tran x = 2^(nullity(M)) (tru 1 neu khong tinh ma tran 0)
// rank(M) + nulltity(M) = so cot = n
// nullity(M) = so cot - rank(M) = n - dim(span(a))
// doan code o duoi tim duoc span -> dim = span.size() 
// n - vec.size()
void insertVector(int mask) {
    for (int i = 0; i < (int)basis.size(); ++i) {
        mask = min(mask, mask ^ basis[i]); }
    if (mask != 0) { basis.push_back(mask); } }
struct Basis {
    int a[20] {}; int t[20] {};
    Basis() { std::fill(t, t + 20, -1); }
    void add(int x, int y = 1E9) {
        for (int i = 0; i < 20; i++) { if (x >> i & 1) {
                if (y > t[i]) { std::swap(a[i], x); std::swap(t[i], y); }
                x ^= a[i]; } } }
    bool query(int x, int y = 0) {
        for (int i = 0; i < 20; i++) { if ((x >> i & 1) && t[i] >= y) {
        x ^= a[i]; } } return x == 0; } };

