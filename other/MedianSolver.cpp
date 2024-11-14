// https://codeforces.com/gym/104901/problem/K
// https://codeforces.com/gym/104901/submission/289791705
class MedianSolver {
public:
  i64 sumLeft = 0, sumRight = 0;
  set<pair<int, int>> left, right;

  void balance() {
    if (left.size() == right.size() || left.size() == right.size() + 1) {
      if (left.size() && right.size() &&
          left.rbegin()->first > right.begin()->first) {
        auto u = *(left.rbegin());
        auto v = *(right.begin());
        left.erase(u);
        right.erase(v);
        sumLeft -= u.first;
        sumRight -= v.first;

        left.insert(v);
        right.insert(u);

        sumLeft += v.first;
        sumRight += u.first;
      }
    } else {
      if (left.size() == 0) {
        auto u = *(right.begin());
        right.erase(u);
        left.insert(u);

        sumRight -= u.first;
        sumLeft += u.first;
        return;
      }

      if (left.size() > right.size() + 1) {
        auto u = *(left.rbegin());
        left.erase(u);
        right.insert(u);

        sumLeft -= u.first;
        sumRight += u.first;
      }
    }
  }

   int getMedian() {
    assert(left.size() != 0);
    balance();
    if (right.size() > left.size()) {
      return right.begin()->first;
    }
    return left.rbegin()->first;
  }


  void insert(const pair<int, int> value) {
    left.insert(value);
    sumLeft += value.first;
    balance();
  }

  void remove(const pair<int, int> &value) {
    balance();

    if (left.find(value) != left.end()) {
      left.erase(value);
      sumLeft -= value.first;
    }

    if (right.find(value) != right.end()) {
      right.erase(value);
      sumRight -= value.first;
    }

    balance();
  }

  // caution: long long
  int getSum() {
    int median = getMedian();

    return (median * left.size() - sumLeft) +
           (sumRight - right.size() * median);
  }
};
