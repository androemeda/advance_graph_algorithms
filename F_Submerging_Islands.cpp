#include <iostream>
#include <vector>
#include <algorithm>
#include <limits>
#define int long long
using namespace std;

int n, m;
vector<vector<int>> adj;
vector<int> levels, topmostlevelreachable, child_count;
vector<bool> visited, is_articulation;

void dfs(int u, int parent, int depth) {
    visited[u] = true;
    levels[u] = depth;
    topmostlevelreachable[u] = depth;
    child_count[u] = 0;
    
    for (int v : adj[u]) {
        if (v == parent) continue;
        if (!visited[v]) {
            // Count this as a DFS‐child of u
            child_count[u]++;
            dfs(v, u, depth + 1);
            topmostlevelreachable[u] = min(topmostlevelreachable[u], topmostlevelreachable[v]);
            
            // NON‐ROOT articulation check
            if (parent != -1 && topmostlevelreachable[v] >= levels[u]) {
                is_articulation[u] = true;
            }
        } else {
            // back‐edge
            topmostlevelreachable[u] = min(topmostlevelreachable[u], levels[v]);
        }
    }
}

void solve() {
    while (true) {
        cin >> n >> m;
        if (!cin || (n == 0 && m == 0))
            return;

        // build graph
        adj.assign(n+1, {});
        for (int i = 0; i < m; i++) {
            int a, b;
            cin >> a >> b;
            adj[a].push_back(b);
            adj[b].push_back(a);
        }

        // init globals
        levels.assign(n+1, 0);
        topmostlevelreachable.assign(n+1, numeric_limits<int>::max());
        visited.assign(n+1, false);
        child_count.assign(n+1, 0);
        is_articulation.assign(n+1, false);

        // run DFS from node 1 (graph is guaranteed connected)
        dfs(1, -1, 0);

        // special root check
        if (child_count[1] > 1) {
            is_articulation[1] = true;
        }

        // count how many islands are articulation points
        int answer = 0;
        for (int i = 1; i <= n; i++) {
            if (is_articulation[i])
                answer++;
        }

        cout << answer << "\n";
    }
}

signed main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    solve();
    return 0;
}
