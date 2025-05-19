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

int n , m;
vector<vector<int>> adj;
vector<bool> visited;
vector<int> parent;

bool dfs(int src){
    visited[src] = true;
    for(int nb : adj[src]){
        if(visited[nb] && parent[src] != nb){
            vector<int> path;
            int curr = src;
            // parent[curr] = src;
            while(curr != -1){
                path.push_back(curr);
                curr = parent[curr];
            }
            reverse(path.begin() , path.end());
            path.push_back(nb);
            cout << path.size() << endl;
            for(int i=0 ; i<path.size() ; i++){
                cout << path[i] << " ";
            }
            return true;
        }
        else if(!visited[nb]){
            parent[nb] = src;
            // visited[nb] = true;
            if(dfs(nb)) return true;
        }
    }
    return false;
}

void solve() {
    cin >> n >> m;

    adj.assign(n+1 , vector<int>());
    for(int i=0 ; i<m ; i++){
        int a,b;
        cin >> a >> b;
        adj[a].push_back(b);
        adj[b].push_back(a);
    }

    visited.assign(n+1 , false);
    parent.assign(n+1 , -1);

    for(int i=1 ; i<=n ; i++){
        if(!visited[i] && dfs(i)) return;
    }

    cout << "IMPOSSIBLE" << endl;
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