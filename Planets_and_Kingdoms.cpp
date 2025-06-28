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

int n,m;
vector<vector<int>> adj;
vector<vector<int>> revadj;
vector<int> leaders;
vector<int> order;
vector<bool> visited;

void getorder(int node){
    visited[node] = true;
    for(int nb : adj[node]){
        if(!visited[nb]){
            getorder(nb);
        }
    }
    order.push_back(node);
}

void dfs(int node , int leader){
    visited[node] = true;
    leaders[node] = leader;
    for(int nb : revadj[node]){
        if(!visited[nb]){
            dfs(nb , leader);
        }
    }
}

void solve() {
    cin >> n >> m;

    adj.assign(n+1 , vector<int>());
    revadj.assign(n+1 , vector<int>());
    leaders.assign(n+1 , -1);
    visited.assign(n+1 , false);

    for(int i=0 ; i<m ; i++){
        int a,b;
        cin >> a >> b;
        adj[a].push_back(b);
        revadj[b].push_back(a);
    }

    for(int i=1 ; i<=n ; i++){
        if(!visited[i]){
            getorder(i);
        }
    }

    for(int i=0 ; i<=n ; i++) visited[i] = false;

    int cnt = 0;

    for(int i=n-1 ; i>=0 ; i--){
        int node = order[i];
        if(!visited[node]){
            cnt++;
            dfs(node , cnt);
        }
    }

    cout << cnt << endl;
    for(int i=1 ; i<=n ; i++) cout << leaders[i] << " ";
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