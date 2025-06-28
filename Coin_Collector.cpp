#include <iostream>
#include <vector>
#include <algorithm>
#include <limits>
#define int long long
using namespace std;

int n, m;
vector<int> coins;
vector<vector<int>> adj, revadj;
vector<bool> visited;
vector<int> order, comp;              
vector<int> compCoins;                
vector<vector<int>> dag;              
vector<int> dp;                       

void dfs1(int u) {
    visited[u] = true;
    for (int v : adj[u]) if (!visited[v]) dfs1(v);
    order.push_back(u);
}

void dfs2(int u, int cid) {
    visited[u] = true;
    comp[u] = cid;
    compCoins[cid] += coins[u];
    for (int v : revadj[u]) if (!visited[v]) dfs2(v, cid);
}

int dfsDP(int c) {
    int &res = dp[c];
    if (res != -1) return res;
    res = compCoins[c];
    int bestNext = 0;
    for (int v : dag[c]) {
        bestNext = max(bestNext, dfsDP(v));
    }
    res += bestNext;
    return res;
}

void solve() {
    cin >> n >> m;
    coins.assign(n+1, 0);
    for (int i = 1; i <= n; i++) {
        cin >> coins[i];
    }

    adj.assign(n+1, {});
    revadj.assign(n+1, {});
    for (int i = 0; i < m; i++) {
        int a, b;
        cin >> a >> b;
        adj[a].push_back(b);
        revadj[b].push_back(a);
    }

    visited.assign(n+1, false);
    order.clear();
    for (int i = 1; i <= n; i++) {
        if (!visited[i]) dfs1(i);
    }

    visited.assign(n+1, false);
    comp.assign(n+1, -1);
    reverse(order.begin(), order.end());
    int cid = 0;
    compCoins.clear();
    for (int u : order) {
        if (!visited[u]) {
            compCoins.push_back(0);
            dfs2(u, cid);
            cid++;
        }
    }
    int C = cid;

    dag.assign(C, {});
    for (int u = 1; u <= n; u++) {
        for (int v : adj[u]) {
            int cu = comp[u], cv = comp[v];
            if (cu != cv) {
                dag[cu].push_back(cv);
            }
        }
    }

    for (int c = 0; c < C; c++) {
        sort(dag[c].begin(), dag[c].end());
        dag[c].erase(unique(dag[c].begin(), dag[c].end()), dag[c].end());
    }

    dp.assign(C, -1);
    int answer = 0;
    for (int c = 0; c < C; c++) {
        answer = max(answer, dfsDP(c));
    }

    cout << answer << "\n";
}

signed main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    solve();
    return 0;
}
