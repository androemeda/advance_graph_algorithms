#include <iostream>
#include <vector>
#include <queue>
#include <limits>
#include <climits>
#define int long long
using namespace std;

struct Edge {
    int u, v, w;
};

int n, m;
vector<Edge> edges;
vector<int> score;

vector<vector<int>> adj, rev_adj;

void dfs(int u, vector<vector<int>> &graph, vector<bool> &visited) {
    visited[u] = true;
    for (int v : graph[u]) {
        if (!visited[v]) dfs(v, graph, visited);
    }
}

void solve() {
    cin >> n >> m;
    edges.clear();
    adj.assign(n + 1, vector<int>());
    rev_adj.assign(n + 1, vector<int>());
    score.assign(n + 1, LLONG_MIN);

    for (int i = 0; i < m; i++) {
        int a, b, x;
        cin >> a >> b >> x;
        edges.push_back({a, b, x});
        adj[a].push_back(b);
        rev_adj[b].push_back(a);
    }

    score[1] = 0;

    // Bellman-Ford relaxation for n-1 times
    for (int i = 0; i < n - 1; i++) {
        for (auto &edge : edges) {
            int u = edge.u, v = edge.v, w = edge.w;
            if (score[u] != LLONG_MIN && score[u] + w > score[v]) {
                score[v] = score[u] + w;
            }
        }
    }

    // Find nodes reachable from 1
    vector<bool> reachable_from_1(n + 1, false);
    dfs(1, adj, reachable_from_1);

    // Find nodes from which we can reach n (reverse DFS)
    vector<bool> reachable_to_n(n + 1, false);
    dfs(n, rev_adj, reachable_to_n);

    // Check for positive cycles reachable from 1 and leading to n
    for (auto &edge : edges) {
        int u = edge.u, v = edge.v, w = edge.w;
        if (score[u] != LLONG_MIN && score[u] + w > score[v]) {
            if (reachable_from_1[u] && reachable_to_n[v]) {
                cout << -1 << endl;  // Infinite max score possible
                return;
            }
        }
    }

    cout << score[n] << endl;  // Maximum score achievable
}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL); cout.tie(NULL);

    int _t = 1;
    // cin >> _t;

    while (_t--) {
        solve();
    }

    return 0;
}


/*
belman-ford --> mantain edge-list and travel over all edges v-1 times

score[1] = 0;

for (auto &edge : edges)

before checking for cycle , first create 2 lists : reachable_from_1 - using adj
                                                   reachable_to_n   - using reverse_adj
*/