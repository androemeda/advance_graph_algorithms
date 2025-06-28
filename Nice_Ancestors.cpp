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

vector<vector<int>> adj;
vector<int> ans;
vector<int> path;

void dfs(int node , int k){

    if(path.size() < k){
        ans[node-1] = -1;
    }
    else{
        ans[node-1] = path[path.size()-k];
    }

    if(adj[node].size() == 1){
        path.push_back(node);
    }

    for(int nb : adj[node]){
        dfs(nb , k);
    }

    if(adj[node].size() == 1){
        path.pop_back();
    }
}

void solve() {

    int n , k;

    cin >> n >> k;

    adj.assign(n+1 , vector<int>());
    ans.assign(n , -1);

    for(int i=2 ; i<=n ; i++){
        int p; 
        cin >> p;
        adj[p].push_back(i);
    }

    dfs(1 , k);

    for(int i=0 ; i<n ; i++){
        cout << ans[i] << " ";
    }

    cout << endl;

}

signed main(){

    ios_base::sync_with_stdio(false);
    cin.tie(NULL); cout.tie(NULL);

    int _t = 1;

    cin >> _t;

    while(_t--){
        solve();
    }

    return 0;
}