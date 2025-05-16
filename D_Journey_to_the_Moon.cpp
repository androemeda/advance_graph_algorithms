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
bool possible = true;

vector<vector<int>> dirs = {{0,1} , {0,-1} , {1,0} , {-1,0}};

int dfs(int curr){
    int ans = 0;

    if(!visited[curr]){
        ans++;
        visited[curr] = true;
        for(int i=0 ; i<adj[curr].size() ; i++){
            ans += dfs(adj[curr][i]);
        }
    }

    return ans;
}

void solve() {
    cin >> n >> m;

    adj.resize(n);
    visited.resize(n , false);

    for(int i=0 ; i<m ; i++){
        int a , b;
        cin >> a >> b;
        adj[a].push_back(b);
        adj[b].push_back(a);
    }

    int totalsum = 0;
    int sumofsquares = 0;

    for(int i=0 ; i<n ; i++){
        int currsize = dfs(i);
        totalsum += currsize;
        sumofsquares += currsize*currsize;
        // cout << currsize << " " ;
    }

    cout << (totalsum*totalsum - sumofsquares)/2 << endl;

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