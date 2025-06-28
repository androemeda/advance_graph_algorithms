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
#include <climits>
#include <numeric>
#define int long long
using namespace std;

int n , m;
vector<int> dp;
vector<int> indegree;
vector<int> topo;
vector<int> parent;
vector<vector<int>> adj;
int mod = 1e9+7;

void solve() {

    cin >> n >> m;

    dp.assign(n+1 , 0);
    adj.assign(n+1 , vector<int>());
    indegree.assign(n+1 , 0);
    parent.assign(n+1 , -1);

    for(int i=0 ; i<m ; i++){
        int u , v;
        cin >> u >> v;
        adj[u].push_back(v);
        indegree[v]++;
    }

    queue<int> q;
    for(int i=1 ; i<=n ; i++){
        if(indegree[i] == 0) q.push(i);
    }
    
    while(!q.empty()){
        int curr = q.front();
        q.pop();
        topo.push_back(curr);
        for(int nb : adj[curr]){
            indegree[nb]--;
            if(indegree[nb] == 0) q.push(nb);
        }
    }

    // for(int i=0 ; i<topo.size() ; i++){
    //     cout << topo[i] << " ";
    // }

    // for(int i=1 ; i<=n ; i++){
    //     cout << i << " : ";
    //     for(int nb : adj[i]) cout << nb << " ";
    //     cout << endl;
    // }

    dp[1] = 1;

    for(int i=0 ; i<topo.size() ; i++){
        int curr = topo[i];
        if(dp[curr] == 0) continue;
        for(int nb : adj[curr]){
            if(dp[nb] < dp[curr] + 1){
                dp[nb] = dp[curr] + 1;
                parent[nb] = curr;
            }
        }
    }

    if(dp[n] == 0) cout << "IMPOSSIBLE" << endl;
    else{
        vector<int> path;
        int curr = n;
        while(curr != -1){
            path.push_back(curr);
            curr = parent[curr];
        }
        cout << dp[n] << endl;
        for(int i=path.size()-1 ; i>=0 ; i--){
            cout << path[i] << " ";
        }
        cout << endl;
    }
}

signed main(){

    ios_base::sync_with_stdio(false);
    cin.tie(NULL); cout.tie(NULL);

    int _t = 1;

    // cin >> t;

    while(_t--){
        solve();
    }

    return 0;
}



// #include <iostream>
// #include <vector>
// #include <queue>
// using namespace std;

// #define int long long

// int n, m;
// vector<vector<int>> adj;
// vector<int> indegree;
// vector<int> dp;
// vector<int> parent;

// void solve() {
//     cin >> n >> m;

//     adj.assign(n + 1, {});
//     indegree.assign(n + 1, 0);
//     parent.assign(n + 1, -1);
//     dp.assign(n + 1, 0); // dp[i] = max cities to reach i from 1

//     for (int i = 0; i < m; i++) {
//         int u, v;
//         cin >> u >> v;
//         adj[u].push_back(v);
//         indegree[v]++;
//     }

//     queue<int> q;
//     dp[1] = 1;

//     for (int i = 1; i <= n; i++) {
//         if (indegree[i] == 0) q.push(i);
//     }

//     while (!q.empty()) {
//         int curr = q.front();
//         q.pop();

//         for (int nb : adj[curr]) {
//             if (dp[nb] < dp[curr] + 1) {
//                 dp[nb] = dp[curr] + 1;
//                 parent[nb] = curr;
//             }
//             indegree[nb]--;
//             if (indegree[nb] == 0) q.push(nb);
//         }
//     }

//     if (dp[n] == 0) {
//         cout << "IMPOSSIBLE\n";
//         return;
//     }

//     vector<int> path;
//     for (int curr = n; curr != -1; curr = parent[curr]) {
//         path.push_back(curr);
//     }

//     reverse(path.begin(), path.end());
//     cout << path.size() << '\n';
//     for (int node : path) {
//         cout << node << ' ';
//     }
//     cout << '\n';
// }

// signed main() {
//     ios_base::sync_with_stdio(false);
//     cin.tie(NULL);
//     solve();
//     return 0;
// }
