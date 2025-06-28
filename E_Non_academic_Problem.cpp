#include <iostream>
#include <vector>
#include <algorithm>
#include <limits>
#define int long long
using namespace std;

int n, m;
vector<vector<int>> adj;
vector<int> levels, topmostlevelreachable, subtree_size;
vector<bool> visited;
vector<pair<int,int>> bridges;
int t_case = 0;

void dfs(int node, int parent, int level) {
    visited[node] = true;
    levels[node] = level;
    topmostlevelreachable[node] = level;
    subtree_size[node] = 1;
    for (int nb : adj[node]) {
        if (nb == parent) continue;
        if (!visited[nb]) {
            dfs(nb, node, level + 1);
            // after returning, we know subtree_size[nb]
            subtree_size[node] += subtree_size[nb];
            topmostlevelreachable[node] = min(topmostlevelreachable[node], topmostlevelreachable[nb]);
            if (topmostlevelreachable[nb] > level) {
                // (node, nb) is a bridge
                bridges.emplace_back(node, nb);
            }
        } else {
            // back‐edge
            topmostlevelreachable[node] = min(topmostlevelreachable[node], levels[nb]);
        }
    }
}

void solve() {
    cin >> n >> m;
    adj.assign(n+1, {});
    for (int i = 0; i < m; i++) {
        int a, b;
        cin >> a >> b;
        adj[a].push_back(b);
        adj[b].push_back(a);
    }

    levels.assign(n+1, 0);
    topmostlevelreachable.assign(n+1, numeric_limits<int>::max());
    visited.assign(n+1, false);
    subtree_size.assign(n+1, 0);
    bridges.clear();

    // run our bridge‐finding DFS
    dfs(1, -1, 0);

    // total possible pairs
    int total_pairs = n * (n - 1) / 2;

    // if no bridges, removing any edge keeps it connected
    if (bridges.empty()) {
        cout << total_pairs << "\n";
    } else {
        // find the bridge whose removal maximizes subtree_size * (n - subtree_size)
        int best_unreach = 0;
        pair<int,int> best_edge = { -1, -1 };
        for (auto [u,v] : bridges) {
            // ensure v is the child in the DFS tree
            if (levels[u] > levels[v]) swap(u,v);
            int s = subtree_size[v];
            int unreach = s * (n - s);
            if (unreach > best_unreach) {
                best_unreach = unreach;
                best_edge = {u, v};
            }
        }
        int min_reachable = total_pairs - best_unreach;
        cout << min_reachable << "\n";
    }
}

signed main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int T;
    cin >> T;
    while (T--) {
        t_case++;
        solve();
    }
    return 0;
}
