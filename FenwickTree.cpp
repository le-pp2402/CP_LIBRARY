template <class T> class BIT {
private:
  int size;
  vector<T> bit;
  vector<T> arr;

public:
  BIT(int size) : size(size), bit(size + 1), arr(size) {}

  void set(int ind, T val) { add(ind, val - arr[ind]); }

  void add(int ind, T val) {
    arr[ind] += val;
    ind++;
    for (; ind <= size; ind += ind & -ind) {
      bit[ind] += val;
    }
  }

  T sum(int ind) {
    ind++;
    T total = 0;
    for (; ind > 0; ind -= ind & -ind) {
      total += bit[ind];
    }
    return total;
  }

  T sum(int l, int r) { return sum(r) - sum(l - 1); }
};
