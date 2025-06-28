#include <iostream>
#include <vector>
#include <algorithm>
#define int long long
using namespace std;

void solve() {
    int n, m;
    cin >> n >> m;
    vector<vector<int>> adj(n+1);
    for(int i = 0; i < m; i++){
        int a, b;
        cin >> a >> b;
        adj[a].push_back(b);
        adj[b].push_back(a);
    }

    vector<int> state(n+1, 0), parent(n+1, -1);
    vector<pair<int,int>> st;
    for(int start = 1; start <= n; start++){
        if(state[start] != 0) continue;
        parent[start] = -1;
        st.clear();
        st.emplace_back(start, 0);
        state[start] = 1;

        while(!st.empty()){
            auto &top = st.back();
            int u = top.first;
            int &idx = top.second;

            if(idx < (int)adj[u].size()){
                int v = adj[u][idx++];
                if(state[v] == 0){
                    parent[v] = u;
                    state[v] = 1;
                    st.emplace_back(v, 0);
                }
                else if(state[v] == 1 && v != parent[u]){
                    vector<int> cycle;
                    cycle.push_back(v);
                    int cur = u;
                    while(cur != v){
                        cycle.push_back(cur);
                        cur = parent[cur];
                    }
                    cycle.push_back(v);
                    reverse(cycle.begin(), cycle.end());
                    cout << cycle.size() << "\n";
                    for(int x : cycle) cout << x << " ";
                    cout << "\n";
                    return;
                }
            } else {
                state[u] = 2;
                st.pop_back();
            }
        }
    }

    cout << "IMPOSSIBLE\n";
}

signed main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    solve();
    return 0;
}
