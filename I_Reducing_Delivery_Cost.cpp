#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
#include <limits>
#define int long long
using namespace std;

const int INF = numeric_limits<int>::max() / 4;

void solve() {
    int n, m, k;
    cin >> n >> m >> k;

    vector<vector<pair<int,int>>> adj(n+1);
    vector<tuple<int,int,int>> edges(m);

    for(int i = 0; i < m; i++){
        int x,y,w;
        cin >> x >> y >> w;
        adj[x].push_back({y,w});
        adj[y].push_back({x,w});
        edges[i] = {x,y,w};
    }

    vector<pair<int,int>> routes(k);
    vector<int> endpoints;
    endpoints.reserve(2*k);

    for(int i = 0; i < k; i++){
        int a,b;
        cin >> a >> b;
        routes[i] = {a,b};
        endpoints.push_back(a);
        endpoints.push_back(b);
    }

    sort(endpoints.begin(), endpoints.end());
    endpoints.erase(unique(endpoints.begin(), endpoints.end()), endpoints.end());
    int P = endpoints.size();

    vector<int> idx(n+1, -1);
    for(int i = 0; i < P; i++){
        idx[endpoints[i]] = i;
    }

    vector<vector<int>> dist(P, vector<int>(n+1, INF));
    for(int pi = 0; pi < P; pi++){
        int src = endpoints[pi];
        auto &d = dist[pi];
        d[src] = 0;
        priority_queue<pair<int,int>,
            vector<pair<int,int>>,
            greater<pair<int,int>>> pq;
        pq.push({0, src});
        while(!pq.empty()){
            auto [du,u] = pq.top(); pq.pop();
            if(du > d[u]) continue;
            for(auto &ed : adj[u]){
                int v = ed.first, w = ed.second;
                if(du + w < d[v]){
                    d[v] = du + w;
                    pq.push({d[v], v});
                }
            }
        }
    }

    vector<int> base(k);
    int64_t best = 0;
    for(int i = 0; i < k; i++){
        int a = routes[i].first, b = routes[i].second;
        int da = idx[a], db = idx[b];
        int d0 = dist[da][b];
        base[i] = d0;
        best += d0;
    }
    
    for(auto &e : edges){
        int u,v,w;
        tie(u,v,w) = e;
        int64_t total = 0;
        for(int i = 0; i < k; i++){
            int a = routes[i].first;
            int b = routes[i].second;
            int da = idx[a], db = idx[b];
            int best_i = base[i];
            int cand = dist[da][u] + dist[db][v];
            if(cand < best_i) best_i = cand;
            cand = dist[da][v] + dist[db][u];
            if(cand < best_i) best_i = cand;
            total += best_i;
        }
        if(total < best) best = total;
    }
    cout << best << "\n";
}

signed main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    solve();
    return 0;
}
