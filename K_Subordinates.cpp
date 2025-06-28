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

int n;
vector<vector<int>> adj;
vector<int> sz;

void dfs(int node){
    for(int nb : adj[node]){
        dfs(nb);
        sz[node] += sz[nb];
    }
}

void solve() {
    cin >> n;
    adj.assign(n+1 , vector<int>());
    for(int i=2 ; i<=n ; i++){
        int p;
        cin >> p;
        adj[p].push_back(i);
    }

    sz.assign(n+1 , 1);

    dfs(1);

    for(int i=1 ; i<=n ; i++){
        cout << sz[i]-1 << " ";
    }
    cout << endl;
}

signed main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL); cout.tie(NULL);

    int _t=1;
    // cin >> _t;
    while(_t--){
        solve();
    }
    return 0;
}