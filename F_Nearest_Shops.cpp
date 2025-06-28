#include <iostream>
#include <vector>
#include <queue>
#include <stack>
#include <algorithm>
#include <cmath>
#include <map>
#include <set>
#include <unordered_map>
#include <unordered_set>
#include <string>
#include <cstring>
#include <cstdio>
#include <cstdlib>
#include <ctime>
#include <cassert>
#include <limits>
#include <numeric>
#include <climits>
#define int long long
using namespace std;

void solve() {
    int n, m, k;
    cin >> n >> m >> k;
    vector<int> shops(k);
    for(int i = 0; i < k; i++) {
        cin >> shops[i];
    }
    vector<vector<int>> adj(n+1);
    vector<pair<int,int>> edges(m);
    for(int i = 0; i < m; i++) {
        int a, b;
        cin >> a >> b;
        adj[a].push_back(b);
        adj[b].push_back(a);
        edges[i] = {a, b};
    }

    const long long INF = LLONG_MAX / 4;
    vector<long long> dist(n+1, INF);
    vector<int> nearest(n+1, 0);
    queue<int> q;

    for(int s : shops) {
        dist[s] = 0;
        nearest[s] = s;
        q.push(s);
    }

    while(!q.empty()) {
        int u = q.front(); q.pop();
        for(int v : adj[u]) {
            if(dist[v] == INF) {
                dist[v] = dist[u] + 1;
                nearest[v] = nearest[u];
                q.push(v);
            }
        }
    }

    vector<long long> ansShop(n+1, INF);
    for(auto &e : edges) {
        int u = e.first, v = e.second;
        if(nearest[u] != nearest[v]) {
            long long cand = dist[u] + 1 + dist[v];
            ansShop[nearest[u]] = min(ansShop[nearest[u]], cand);
            ansShop[nearest[v]] = min(ansShop[nearest[v]], cand);
        }
    }

    for(int i = 1; i <= n; i++) {
        if(nearest[i] != i) {
            cout << (dist[i] >= INF/2 ? -1 : dist[i]);
        } else {
            cout << (ansShop[i] >= INF/2 ? -1 : ansShop[i]);
        }
        if(i < n) cout << ' ';
    }
    cout << '\n';
}

signed main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL); cout.tie(NULL);

    int _t = 1;
    // cin >> _t;
    while(_t--){
        solve();
    }
    return 0;
}
