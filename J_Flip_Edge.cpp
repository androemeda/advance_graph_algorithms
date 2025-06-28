#include <iostream>
#include <vector>
#include <queue>
#include <limits>
#include <climits>
#define int long long
using namespace std;

int INF = LONG_MAX;

void solve() {
    int N, M;
    int X;
    cin >> N >> M >> X;
    vector<vector<int>> g0(N), g1(N);
    for(int i = 0; i < M; i++){
        int u, v;
        cin >> u >> v;
        --u; --v;
        g0[u].push_back(v);
        g1[v].push_back(u);
    }
    int tot = 2 * N;
    vector<int> dist(tot, INF);

    priority_queue<pair<int,int>, vector<pair<int,int>>, greater<>> pq;
    auto push = [&](int s, int d) {
        if(d < dist[s]) {
            dist[s] = d;
            pq.push({d, s});
        }
    };
    push(0, 0);

    while(!pq.empty()) {
        auto [d, st] = pq.top(); pq.pop();
        if(d > dist[st]) continue;
        int p = st / N;
        int v = st % N;
        int st2 = (p^1)*N + v;
        push(st2, d + X);
        if(p == 0) {
            for(int u: g0[v]) {
                int nxt = p*N + u;
                push(nxt, d + 1);
            }
        } else {
            for(int u: g1[v]) {
                int nxt = p*N + u;
                push(nxt, d + 1);
            }
        }
    }
    int ans = min(dist[0*N + (N-1)], dist[1*N + (N-1)]);
    cout << ans << "\n";
}

signed main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    solve();
    return 0;
}
