// neu tren duong di tu u -> v chua chu trinh am thi do dai duong di ngan nhat tu u -> v se la am
// vo cuc. Vi vay nen su xuat hien cua chu trinh am trong do thi se khien mot so cap dinh khong 
// ton tai duong di ngan nhat.

const long long INF = 2000000000000000000LL;
struct Edge {
    int u, v;
    long long w; 
};
void bellmanFord(int n, int S, vector<Edge> &e, vector<long long> &D, vector<int> &trace) {
    // e: danh sach canh
    // n: so dinh
    // S: dinh bat dau
    // D: do dai duong di ngan nhat
    // trace: mang truy vet
    // INF neu co duong di
    // -INF neu co duong di am vo cuc
    D.resize(n, INF);
    trace.resize(n, -1);

    D[S] = 0;
    for(int T = 1; T < n; T++) {
        for (auto E : e) {
            int u = E.u;
            int v = E.v;
            long long w = E.w;
            if (D[u] != INF && D[v] > D[u] + w) {
                D[v] = D[u] + w;
                trace[v] = u;
            }
        }
    }
}

vector<int> trace_path(vector<int> &trace, int S, int u) {
    if (u != S && trace[u] == -1) return vector<int>(0); 

    vector<int> path;
    while (u != -1) { 
        path.push_back(u);
        u = trace[u];
    }
    reverse(path.begin(), path.end()); 

    return path;
}


bool findNegativeCycle(int n, vector<long long> &D, vector<int> &trace, vector<int> &negCycle) {
    // mang D va trace da duoc chay qua thuat toan Bellmanford
    int negStart = -1; // dinh bat dau
    for (auto E : e) {
        int u = E.u;
        int v = E.v;
        long long w = E.w;
        if (D[u] != INF && D[v] > D[u] + w) {
            D[v] = -INF;
            trace[v] = u;
            negStart = v; // da tim thay -INF
        }
    }

    if (negStart == -1) return false; // khong co chu trinh am

    int u = negStart;
    for (int i = 0; i < n; i++) {
        u = trace[u]; // dua u ve chu trinh am
    }

    negCycle = vector<int>(1, u);
    for (int v = trace[u]; v != u; v = trace[u]) {
        negCycle.push_back(v); // truy vet mot dong
    }
    reverse(negCycle.begin(), negCycle.end());

    return true;
}
