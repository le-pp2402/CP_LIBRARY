#include <ext/pb_ds/assoc_container.hpp>
const int RANDOM = chrono::high_resolution_clock::now().time_since_epoch().count();
struct chash { int operator()(int x) const { return x ^ RANDOM; } };
struct pairhash { // change to random int operator()(pair<int, int> x) const { return x.first* 31 + x.second; } };
gp_hash_table<int, int, chash> table;
using namespace __gnu_pbds;
struct chash { };
gp_hash_table<pair<int, int>, int, chash> ex;
gp_hash_table<int, int> Ox, Oy;
struct custom_hash {
    static uint64_t splitmix64(uint64_t x) {
        x += 0x9e3779b97f4a7c15;
        x = (x ^ (x >> 30)) * 0xbf58476d1ce4e5b9;
        x = (x ^ (x >> 27)) * 0x94d049bb133111eb;
        return x ^ (x >> 31);
    }
    size_t operator()(uint64_t x) const {
        static const uint64_t FIXED_RANDOM = chrono::steady_clock::now().time_since_epoch().count();
        return splitmix64(x + FIXED_RANDOM);
    }
};
unordered_map<long long, int, custom_hash> safe_map;
gp_hash_table<long long, int, custom_hash> safe_hash_table;
