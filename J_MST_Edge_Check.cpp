#include <iostream>
#include <vector>
#include <algorithm>
#include <limits>
#define int long long
using namespace std;

class DSU2 {
public:
    vector<int> parent, sz;
    DSU2(int n): parent(n), sz(n,1) {
        for(int i = 0; i < n; i++) parent[i] = i;
    }
    int findRoot(int a) {
        if(parent[a] == a) return a;
        return parent[a] = findRoot(parent[a]);
    }
    void unite(int a, int b) {
        a = findRoot(a);
        b = findRoot(b);
        if(a == b) return;
        if(sz[a] < sz[b]) swap(a,b);
        parent[b] = a;
        sz[a] += sz[b];
    }
};

void solve() {
    int n, m;
    cin >> n >> m;
    struct Edge { int w, u, v, idx; };
    vector<Edge> edges;

    for(int i = 0; i < m; i++){
        int a, b, w;
        cin >> a >> b >> w;
        edges.push_back({w, a, b, i});
    }
    // sort by weight
    sort(edges.begin(), edges.end(), [](auto &A, auto &B){
        return A.w < B.w;
    });

    DSU2 dsu(n+1);
    vector<string> ans(m, "NO");

    int i = 0;
    while(i < m) {
        int j = i;
        // find range [i, j) with same weight
        while(j < m && edges[j].w == edges[i].w) j++;

        // first pass: mark which edges in [i,j) can go into MST
        vector<pair<int,int>> toUnion;
        for(int k = i; k < j; k++){
            auto &e = edges[k];
            int ru = dsu.findRoot(e.u), rv = dsu.findRoot(e.v);
            if(ru != rv) {
                ans[e.idx] = "YES";
                toUnion.emplace_back(ru, rv);
            }
        }
        // second pass: unite all those
        for(auto &p : toUnion) {
            dsu.unite(p.first, p.second);
        }
        i = j;
    }

    // output in original order
    for(int t = 0; t < m; t++){
        cout << ans[t] << "\n";
    }
}

signed main(){
    solve();
    return 0;
}
