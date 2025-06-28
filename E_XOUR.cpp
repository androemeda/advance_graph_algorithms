#include <iostream>
#include <vector>
#include <algorithm>
#include <numeric>
#define int long long
using namespace std;

int n, m;

// (DSU1 and DSU2 are now unused but left in your template)
class DSU1 {
public:
    vector<int> parent;
    DSU1(int n) { parent.resize(n); iota(parent.begin(), parent.end(), 0); }
    int findRoot(int a) {
        if (a == parent[a]) return a;
        return parent[a] = findRoot(parent[a]);
    }
    void unite(int a, int b) {
        a = findRoot(a); b = findRoot(b);
        if (a != b) parent[b] = a;
    }
};
class DSU2 {
public:
    vector<int> parent, sz;
    DSU2(int n) : parent(n), sz(n,1) { iota(parent.begin(), parent.end(), 0); }
    int findRoot(int a) {
        if (a == parent[a]) return a;
        return parent[a] = findRoot(parent[a]);
    }
    void unite(int a, int b) {
        a = findRoot(a); b = findRoot(b);
        if (a == b) return;
        if (sz[a] < sz[b]) { parent[a] = b; sz[b] += sz[a]; }
        else           { parent[b] = a; sz[a] += sz[b]; }
    }
};

void solve() {
    cin >> n;
    vector<int> a(n);
    for (int i = 0; i < n; i++) cin >> a[i];

    // build (block, idx) list
    vector<pair<int,int>> v;
    v.reserve(n);
    for (int i = 0; i < n; i++) {
        v.emplace_back(a[i] >> 2, i);
    }
    sort(v.begin(), v.end(),
         [](auto &A, auto &B){
           if (A.first != B.first) return A.first < B.first;
           return A.second < B.second;
         });

    vector<int> res(n);
    int i = 0;
    while (i < n) {
        int j = i+1;
        while (j < n && v[j].first == v[i].first) j++;

        // group is v[i..j-1]
        if (j - i == 1) {
            // single element, stays in place
            int idx = v[i].second;
            res[idx] = a[idx];
        } else {
            // collect indices & values
            vector<int> idxs;
            idxs.reserve(j-i);
            for (int k = i; k < j; k++)
                idxs.push_back(v[k].second);
            sort(idxs.begin(), idxs.end());

            vector<int> vals;
            vals.reserve(j-i);
            for (int idx : idxs)
                vals.push_back(a[idx]);
            sort(vals.begin(), vals.end());

            for (int k = 0; k < (int)idxs.size(); k++)
                res[idxs[k]] = vals[k];
        }
        i = j;
    }

    // output
    for (int k = 0; k < n; k++)
        cout << res[k] << (k+1<n?' ':'\n');
}

signed main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int T;
    cin >> T;
    while (T--) solve();
    return 0;
}
