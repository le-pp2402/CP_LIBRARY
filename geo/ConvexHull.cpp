// A -> B -> C nguoc chieu kim dong ho
bool ccw(const Point &A, const Point &B, const Point &C) {
    return 1LL * (B.x - A.x) * (C.y - A.y) - 1LL * (C.x - A.x) * (B.y - A.y) > 0;
}
// bao loi thu tu cac diem theo chieu kim dong ho
vector<Point> convexHull(vector<Point> p, int n) {
    sort(p.begin(), p.end(), [](const Point &A, const Point &B) {
        if (A.x != B.x) return A.x < B.x;
        return A.y < B.y;
    });
    vector<Point> hull;
    hull.push_back(p[0]);
    for (int i = 1; i < n; ++i) {
        while (hull.size() >= 2 && ccw(hull[hull.size() - 2], hull.back(), p[i])) hull.pop_back();
        hull.push_back(p[i]);
    }
    for (int i = n - 2; i >= 0; --i) {
        while (hull.size() >= 2 && ccw(hull[hull.size() - 2], hull.back(), p[i])) hull.pop_back();
        hull.push_back(p[i]);
    }
    if (n > 1) hull.pop_back(); return hull; }
