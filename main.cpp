#include <bits/stdc++.h>
using namespace std;

typedef long long i64;

// Represents a spell line with integer slope and intercept
struct Line {
    i64 num, den; // represents (b - x) / (b - a) as (num / den)
    int id;

    // At a given x, return the numerator and denominator of the probability
    pair<i64, i64> eval(i64 x, const pair<i64, i64>& range) const {
        auto [a, b] = range;
        if (x <= a) return {1, 1};
        if (x > b) return {0, 1};
        return {b - x, b - a};
    }
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;
    vector<tuple<i64, i64, int>> spells, degenerate;
    unordered_map<int, pair<i64, i64>> id2range;
    for (int i = 0; i < n; ++i) {
        i64 a, b;
        cin >> a >> b;
        id2range[i + 1] = {a, b};
        if (a == b) degenerate.emplace_back(a, b, i + 1);
        else spells.emplace_back(a, b, i + 1);
    }

    sort(spells.begin(), spells.end());
    sort(degenerate.begin(), degenerate.end());

    vector<int> hull;
    for (auto [a, b, id] : spells) {
        while (!hull.empty() && id2range[hull.back()].second <= b)
            hull.pop_back();
        hull.push_back(id);
    }

    int m;
    cin >> m;
    while (m--) {
        i64 x;
        cin >> x;

        int bestId = -1;
        i64 bestNum = -1, bestDen = 1;

        auto better = [&](int u, int v) -> bool {
            auto [au, bu] = id2range[u];
            auto [av, bv] = id2range[v];
            i64 nu = (x <= au) ? 1 : (x > bu ? 0 : bu - x);
            i64 du = (x <= au || x > bu) ? 1 : bu - au;
            i64 nv = (x <= av) ? 1 : (x > bv ? 0 : bv - x);
            i64 dv = (x <= av || x > bv) ? 1 : bv - av;
            return nu * dv > nv * du;
        };

        // Binary search on convex hull
        int lo = 0, hi = (int)hull.size() - 1;
        while (lo < hi) {
            int mid = (lo + hi) / 2;
            if (better(hull[mid], hull[mid + 1])) hi = mid;
            else lo = mid + 1;
        }

        if (!hull.empty()) {
            auto [a, b] = id2range[hull[lo]];
            if (x <= a) bestNum = 1, bestDen = 1;
            else if (x > b) bestNum = 0, bestDen = 1;
            else bestNum = b - x, bestDen = b - a;
            bestId = hull[lo];
        }

        // Binary search on degenerate spells
        lo = 0, hi = (int)degenerate.size() - 1;
        while (lo <= hi) {
            int mid = (lo + hi) / 2;
            if (x <= get<0>(degenerate[mid])) {
                if (bestId == -1 || bestNum * 1 < 1 * bestDen) {
                    bestId = get<2>(degenerate[mid]);
                    bestNum = 1;
                    bestDen = 1;
                }
                hi = mid - 1;
            } else {
                lo = mid + 1;
            }
        }

        if (bestId == -1) bestId = 1;
        cout << bestId << " ";
    }

    cout << '\n';
    return 0;
}
