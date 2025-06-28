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
vector<int> height;
vector<bool> visited;
int ans = 0;

void dfs(int node) {
    visited[node] = true;
    int mx1 = 0, mx2 = 0;
    for (int nb : adj[node]) {
        if (!visited[nb]) {
            dfs(nb);
            int h = height[nb] + 1;
            if (h > mx1) {
                mx2 = mx1;
                mx1 = h;
            } else if (h > mx2) {
                mx2 = h;
            }
        }
    }
    ans = max(ans, mx1 + mx2);
    height[node] = mx1;
}

void solve() {
    cin >> n;
    adj.assign(n+1 , vector<int>());
    height.assign(n+1 , 1);
    visited.assign(n+1 , false);
    for(int i=0 ; i<n-1 ; i++){
        int a , b;
        cin >> a >> b;
        adj[a].push_back(b);
        adj[b].push_back(a);
    }

    dfs(1);

    cout << ans << endl;
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