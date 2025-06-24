// https://github.com/kth-competitive-programming/kactl/blob/main/content/data-structures/LineContainer.h
struct Line {
    mutable i64 k, m, p;
    bool operator<(const Line& o) const { return k < o.k; }  
    bool operator<(i64 x) const { return p < x; }
};

struct LineContainer : multiset<Line, less<>> {
    static const i64 inf = LLONG_MAX;
    bool isMin;  // true for min, false for max
    
    LineContainer(bool getMin = true) : isMin(getMin) {}
    
    i64 div(i64 a, i64 b) {
        return a / b - ((a ^ b) < 0 && a % b); 
    }
    
    bool isect(iterator x, iterator y) {
        if (y == end()) return x->p = inf, 0;
        if (x->k == y->k) x->p = x->m > y->m ? inf : -inf;
        else x->p = div(y->m - x->m, x->k - y->k);
        return x->p >= y->p;
    }
    
    void add(i64 k, i64 m) {
        if (!isMin) k = -k, m = -m;  // negate for max query
        auto z = insert({k, m, 0}), y = z++, x = y;
        
        while (isect(y, z)) {
            z = erase(z);
        }
        
        if (x != begin() && isect(--x, y)) 
            isect(x, y = erase(y));
        
        while ((y = x) != begin() && (--x)->p >= y->p)
            isect(x, erase(y));
    }
    
    i64 query(i64 x) {
        assert(!empty());
        auto l = *lower_bound(x);
        debug(x, l.k, l.m, l.p);
        i64 res = l.k * x + l.m;
        return isMin ? res : -res;  // negate result for max query
    }
};
