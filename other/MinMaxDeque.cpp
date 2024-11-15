// author: Le Phi Phat
template <class T> class minStack {
public:
  stack<pair<T, T>> st;
  T getMin() { return st.top().second; }
  T empty() { return st.empty(); }
  int size() { return st.size(); }
  void push(T x) {
    T mn = x;
    if (!empty()) mini(mn, getMin());
    st.push(make_pair(x, mn));
  }
  void pop() { st.pop(); }
  T top() { return st.top().first; }
  void swap(minStack<T> &another) { st.swap(another.st); }
};
template <class T> class minDeque {
public:
  minStack<T> stackF, stackB, stackTmp;
  void rebalance() {
    bool flag = false;
    if (stackF.empty()) {
      stackF.swap(stackB);
      flag = true;
    }
    int sz = stackF.size() / 2;
    while (sz--) {
      stackTmp.push(stackF.top());
      stackF.pop();
    }
    while (!stackF.empty()) {
      stackB.push(stackF.top());
      stackF.pop();
    }
    while (!stackTmp.empty()) {
      stackF.push(stackTmp.top());
      stackTmp.pop();
    }
    if (flag) stackF.swap(stackB);
  }
  bool empty() { return (stackF.empty() && stackB.empty()); }
  int size() { return (stackB.size() + stackF.size()); }
  void push_back(T x) { stackB.push(x); }
  void push_front(T x) { stackF.push(x); }
  void pop_back() {
    assert(stackB.size() || stackF.size());
    if (stackB.empty())
      rebalance();
    stackB.pop();
  }
  void pop_front() {
    assert(stackB.size() || stackF.size());
    if (stackF.empty())
      rebalance();
    stackF.pop();
  }
  T back() {
    if (stackB.empty())
      rebalance();
    return stackB.top();
  }
  T front() {
    if (stackF.empty())
      rebalance();
    return stackF.top();
  }
  T getMin() {
    assert(stackB.size() || stackF.size());
    if (stackF.empty())
      return stackB.getMin();
    if (stackB.empty())
      return stackF.getMin();
    return min(stackF.getMin(), stackB.getMin());
  }
};
void print(minDeque<int> de) {
  cout << "[ ";
  while (de.stackF.size()) { cout << de.stackF.top() << ", "; de.stackF.pop(); }
  vector<int> v;
  while (de.stackB.size()) { v.push_back(de.stackB.top()); de.stackB.pop(); }
  while (not v.empty()) { cout << v.back() << ", "; v.pop_back(); }
  cout << "]\n";
}
