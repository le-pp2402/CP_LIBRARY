
using i64 = long long;

template<class T>
struct Edge {
  int u, v;
  T cost;
};

// Chỉ xét đơn đồ thị, trường hợp đa đồ thì hãy tiền xử lý dữ liệu trước 
// get max
template<class T>
struct BellmanFord {
  const T INF = numeric_limits<T>::max();
  const T N_INF = numeric_limits<T>::min();

  vector<Edge<T>> edges;
  vector<T> dis;
  vector<int> trace;
  int n, negSt;
  bool hasNegCycle;

  int st = 0;

  BellmanFord(int n, int st = -1) {
    this->n = n;
    // from a source 
    if (st != -1) { 
      dis.assign(n, INF);
      dis[st] = 0;
    } else { 
      // just find cycle
      dis.assign(n, 0);
    }
    trace.assign(n, -1);
    this->st = st;
    this->hasNegCycle = false;
  }


  void addEdge(int u, int v, T w) {
    edges.push_back(Edge<T>(u, v, w));
  }

  vector<int> getPath(int dest = -1) {
    assert(st != -1);

    if (dest != st && trace[dest] == -1) return vector<int>();

    vector<int> res;

    while (dest != -1) {
      res.push_back(dest);
      dest = trace[dest];
    }

    reverse(res.begin(), res.end());
    return res;
  }
  
  vector<int> getCycle() {
    assert(hasNegCycle == true && negSt >= 0);

    for (int _ = 0; _ < n; _++) {
      negSt = trace[negSt];
    }

    debug(negSt);
    vector<int> res(1, negSt);
    for (int v = trace[negSt]; v != negSt; v = trace[v]) {
      debug(v);
      res.push_back(v);
    }
    // res.push_back(negSt);
    reverse(res.begin(), res.end());
    return res;
  }

  void calc() {
    for (int _ = 0; _ < n - 1; _++) {
      for (auto &e: edges) {
        if (dis[e.u] != INF && dis[e.v] > dis[e.u] + e.cost) {
          dis[e.v] = dis[e.u] + e.cost;
          trace[e.v] = e.u;
        }
      }
    }

    for (auto &e: edges) {
      if (dis[e.u] != INF && dis[e.v] > dis[e.u] + e.cost) {
        trace[e.v] = e.u;
        this->hasNegCycle = true;
        this->negSt = e.v;
      }
    }
  }
};
