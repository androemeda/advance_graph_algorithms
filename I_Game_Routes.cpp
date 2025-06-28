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
vector<vector<int>> adj;
int mod = 1e9+7;

void solve() {

    cin >> n >> m;

    dp.assign(n+1 , 0); //number of paths that started from 1 and end on i.
    adj.assign(n+1 , vector<int>());
    indegree.assign(n+1 , 0);

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

    dp[1] = 1;
    
    for(int i=0 ; i<topo.size() ; i++){
        int curr = topo[i];
        for(int nb : adj[curr]){
            dp[nb] = (dp[nb]%mod + dp[curr]%mod)%mod;
        }
    }

    cout << dp[n]%mod << endl;

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