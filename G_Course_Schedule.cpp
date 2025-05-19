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
#define int long long
using namespace std;

int n , m;
vector<vector<int>> adj;
vector<int> indegree;

void solve() {
    cin >> n >> m;

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

    vector<int> ans;

    while(!q.empty()){
        int curr = q.front();
        ans.push_back(curr);
        q.pop();
        for(int nb : adj[curr]){
            indegree[nb]--;
            if(indegree[nb] == 0){
                q.push(nb);
            }
        }
    }

    if(ans.size() != n) cout << "IMPOSSIBLE";
    else {
        for(int i=0 ; i<n ; i++){
            cout << ans[i] << " ";
        }
    }

    cout << endl;
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