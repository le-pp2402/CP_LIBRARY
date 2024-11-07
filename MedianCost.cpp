template <class C> struct Q {
  std::priority_queue<int, std::vector<int>, C> q1, q2;
  int size = 0;
  i64 sum = 0;

  void insert(int x) {
    size += 1;
    q1.push(x);
    sum += x;
  }

  void erase(int x) {
    size -= 1;
    q2.push(x);
    sum -= x;
    while (!q2.empty() && q1.top() == q2.top()) {
      q1.pop();
      q2.pop();
    }
  }

  int top() { return q1.top(); }

  bool empty() { return size == 0; }
};

struct Node {
  Q<std::less<int>> l;
  Q<std::greater<int>> r;

  void insert(int x) {
    if (l.empty() || l.top() >= x) {
      l.insert(x);
    } else {
      r.insert(x);
    }

    if (r.size + 1 < l.size) {
      r.insert(l.top());
      l.erase(l.top());
    } else if (l.size < r.size) {
      l.insert(r.top());
      r.erase(r.top());
    }
  }

  void erase(int x) {
    if (l.top() >= x) {
      l.erase(x);
    } else {
      r.erase(x);
    }

    if (r.size + 1 < l.size) {
      r.insert(l.top());
      l.erase(l.top());
    } else if (l.size < r.size) {
      l.insert(r.top());
      r.erase(r.top());
    }
  }

  // Cost to make all elements is equal median.
  i64 get_ans() { return r.sum - l.sum + l.top() * (l.size > r.size); }
};
