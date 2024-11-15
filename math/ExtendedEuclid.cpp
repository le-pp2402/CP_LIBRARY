// Dung Extended Euclid de tim nghiem cua phuong trinh ax + by = gcd(a, b).
// G/s ket qua tra ve la (x0, y0), ho nghiem cua phuong trinh se la (x_0+kb/d,y_0-ka/d) voi k∈Z.
// Phuong trinh tong quat ax + by = d chi co nghiem khi d chia het cho gcd(a, b).
// a x + b y = gcd(a, b)
template<typename T>
T extgcd(T a, T b, T &x, T &y) { T g = a; x = 1; y = 0;
    if (b != 0) g = extgcd(b, a % b, y, x), y -= (a / b) * x; return g; }
