struct Point {
  i64 x, y;
  Point() { x = y = 0.0; }
  Point(i64 x, i64 y) : x(x), y(y) {}

  Point operator+(const Point &a) const { return Point(x + a.x, y + a.y); }
  Point operator-(const Point &a) const { return Point(x - a.x, y - a.y); }
  Point operator*(i64 k) const { return Point(x * k, y * k); }
  Point operator/(i64 k) const { return Point(x / k, y / k); }
};

struct Line { // Ax + By = C
  i64 a, b, c;
  Line(i64 a = 0, i64 b = 0, i64 c = 0) : a(a), b(b), c(c) {}
  Line(Point A, Point B) {
    a = B.y - A.y;
    b = A.x - B.x;
    c = a * A.x + b * A.y;
  }
};

bool bl(Line line, Point p) { return (line.a * p.x + line.b * p.y == line.c); }
