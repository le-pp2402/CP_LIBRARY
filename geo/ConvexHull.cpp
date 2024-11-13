// A -> B -> C đi theo thứ tự ngược chiều kim đồng hồ
bool ccw(const Point &A, const Point &B, const Point &C) {
    return 1LL * (B.x - A.x) * (C.y - A.y) - 1LL * (C.x - A.x) * (B.y - A.y) > 0;
}

// Trả về bao lồi với thứ tự các điểm được liệt kê theo chiều kim đồng hồ
vector<Point> convexHull(vector<Point> p, int n) {
    // Sắp xếp các điểm theo tọa độ x, nếu bằng nhau sắp xếp theo y
    sort(p.begin(), p.end(), [](const Point &A, const Point &B) {
        if (A.x != B.x) return A.x < B.x;
        return A.y < B.y;
    });

    // Tập bao lồi
    vector<Point> hull;
    hull.push_back(p[0]);

    // Dựng bao trên
    for (int i = 1; i < n; ++i) {
        while (hull.size() >= 2 && ccw(hull[hull.size() - 2], hull.back(), p[i])) {
            hull.pop_back();
        }
        hull.push_back(p[i]);
    }

    // Tiếp tục dựng bao dưới
    for (int i = n - 2; i >= 0; --i) {
        while (hull.size() >= 2 && ccw(hull[hull.size() - 2], hull.back(), p[i])) {
            hull.pop_back();
        }
        hull.push_back(p[i]);
    }

    // Xoá đỉểm đầu được lặp lại ở cuối
    if (n > 1) hull.pop_back();

    return hull;
}
