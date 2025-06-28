#include <iostream>
#include <vector>
#include <algorithm>
#include <limits>
#define int long long
using namespace std;

int n, m;
vector<vector<int>> adj;
vector<int> levels, topmostlevelreachable;
vector<bool> visited;
vector<vector<int>> ans;
int caseNo = 0;

void dfs(int node, int parent, int level) {
    visited[node] = true;
    levels[node] = level;
    topmostlevelreachable[node] = level;
    for (int nb : adj[node]) {
        if (nb == parent) continue;
        if (!visited[nb]) {
            dfs(nb, node, level + 1);
            topmostlevelreachable[node] = min(topmostlevelreachable[node], topmostlevelreachable[nb]);
            if (topmostlevelreachable[nb] > level) {
                // record bridge; we'll normalize later
                ans.push_back({ node, nb });
            }
        } else {
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
    ans.clear();

    // graph is guaranteed connected
    dfs(1, -1, 0);

    // normalize so that u < v
    for (auto &e : ans) {
        if (e[0] > e[1]) 
            swap(e[0], e[1]);
    }
    // sort by u, then v
    sort(ans.begin(), ans.end(),
         [](const vector<int>& A, const vector<int>& B) {
            if (A[0] != B[0]) return A[0] < B[0];
            return A[1] < B[1];
         });

    cout << "Caso #" << caseNo << "\n";
    if (ans.empty()) {
        cout << "Sin bloqueos\n";
    } else {
        cout << ans.size() << "\n";
        for (auto &e : ans) {
            cout << e[0] << " " << e[1] << "\n";
        }
    }
}

signed main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int NC;
    cin >> NC;
    while (NC--) {
        caseNo++;
        solve();
    }
    return 0;
}
