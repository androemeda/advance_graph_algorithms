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
vector<bool> visited;
vector<vector<int>> adj;

vector<vector<int>> dirs = {{0,1} , {0,-1} , {1,0} , {-1,0}};

void dfs(int node){
    if(!visited[node]){
        visited[node] = true;
        for(int i=0 ; i<adj[node].size() ; i++){
            dfs(adj[node][i]);
        }
    }
}

void solve() {
    cin >> n >> m;

    adj.resize(n+1);
    visited.resize(n+1 , false);

    for(int i=0 ; i<m ; i++){
        int a , b;
        cin >> a >> b;
        adj[a].push_back(b);
        adj[b].push_back(a);
    }

    int comps = 0;

    vector<int> joins;

    for(int i=1 ; i<=n ; i++){
        if(!visited[i]){
            comps++;
            dfs(i);
            joins.push_back(i);
        }
    }

    cout << comps-1 << endl;
    for(int i=1 ; i<joins.size() ; i++){
        cout << joins[i-1] << " " << joins[i];
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