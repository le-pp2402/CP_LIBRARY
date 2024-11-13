// Khoang cach diem va duong thang
typedef double db;
struct vec {
    db x, y;
    vec(db _x = 0, db _y = 0) : x(_x), y(_y) {}
    db dot(const vec &other) { // Compute the dot product
        return x * other.x + y * other.y;
    }
    db cross(const vec &other) { // Compute the cross product
        return x * other.y - y * other.x;
    }
    db length() const {
        return sqrt(x * x + y * y);
    }
};
using point = vec; // or use 'typedef vec point'
vec operator - (const point &B, const point &A) { // vecAB = B - A
    return vec(B.x - A.x, B.y - A.y);
}
// if isSegment is true, AB is a segment, not a line.
db linePointDist(const point &A, const point &B, const point &C, bool isSegment) {
    db dist = abs((B - A).cross(C - A)) / (A - B).length();
    if (isSegment) {
        db dot1 = (A - B).dot(C - B);
        if (dot1 < 0) return (B - C).length();
        db dot2 = (B - A).dot(C - A);
        if (dot2 < 0) return (A - C).length();
    }
    return dist;
}
// Giao diem cua hai duong thang
const double eps = 1e-9;
int sign(double x) {
    if (x > eps) return 1;
    if (x < -eps) return -1;
    return 0;
}
double cross(Vec AB, Vec AC) {
    return AB.x * AC.y - AC.x * AB.y;
}
double dot(Vec AB, Vec AC) {
    return AB.x * AC.x + AB.y * AC.y;
}
bool intersect(Point A, Point B, Point C, Point D) {
    int ABxAC = sign(cross(B - A, C - A));
    int ABxAD = sign(cross(B - A, D - A));
    int CDxCA = sign(cross(D - C, A - C));
    int CDxCB = sign(cross(D - C, B - C));
    if (ABxAC == 0 || ABxAD == 0 || CDxCA == 0 || CDxCB == 0) {
        // C on segment AB if ABxAC = 0 and CA.CB <= 0
        if (ABxAC == 0 && sign(dot(A - C, B - C)) <= 0) return true;
        if (ABxAD == 0 && sign(dot(A - D, B - D)) <= 0) return true;
        if (CDxCA == 0 && sign(dot(C - A, D - A)) <= 0) return true;
        if (CDxCB == 0 && sign(dot(C - B, D - B)) <= 0) return true;
        return false;
    }
    return (ABxAC * ABxAD < 0 && CDxCA * CDxCB < 0);
}
// Duong trung truc
Line Perpendicular_Bisector(Point A, Point B) {
    Point M = (A + B) / 2;
    Line d = Line(A, B);
    // the equation of a perpendicular line has the form: -Bx + Ay = D
    double D = -d.b * M.x + d.a * M.y;
    return Line(-d.b, d.a, D);
}
Point intersect(Line d1, Line d2) {
    double det = d1.a * d2.b - d2.a * d1.b;
    // det != 0 because d1 is perpendicular to d2
    return Point((d2.b * d1.c - d1.b * d2.c) / det, (d1.a * d2.c - d2.a * d1.c) / det);
}
// phep doi xung
Point Symmetry(Point X, Line d) {
    // the equation of a perpendicular line has the form: -Bx + Ay = D
    double D = -d.b * X.x + d.a * X.y;
    Line d2 = Line(-d.b, d.a, D);
    Point Y = intersect(d, d2);
    Point X2 = Point(2 * Y.x - X.x, 2 * Y.y - X.y);
    return X2;
}
// phep quay
Point Rotations(Point A, Point C, double rad) {
    Point A2 = A - C;
    Point B2 = Point(A2.x * cos(rad) - A2.y * sin(rad), A2.x * sin(rad) + A2.y * cos(rad));
    Point B = B2 + C;
    return B;
}
