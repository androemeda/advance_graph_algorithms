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
vector<vector<pair<int,int>>> adj;
vector<int> mn;
vector<int> mx;
vector<int> ways;
vector<int> dist;
int mod = 1e9+7;

void solve() {

    cin >> n >> m;

    adj.assign(n+1 , vector<pair<int,int>>());
    mn.assign(n+1 , LLONG_MAX);
    mx.assign(n+1 , 0);
    ways.assign(n+1 , 0);
    dist.assign(n+1 , LLONG_MAX);

    for(int i= 0 ; i<m ; i++){
        int a , b , c;
        cin >> a >> b >> c;
        adj[a].push_back({b , c});
    }

    priority_queue<tuple<int,int> , vector<tuple<int,int>> , greater<> > pq; // dist , node

    pq.push({0 , 1});
    mn[1] = 0;
    mx[1] = 0;
    ways[1] = 1;
    dist[1] = 0;

    while(!pq.empty()){
        auto [d , node] = pq.top();
        pq.pop();

        if(d > dist[node]) continue;

        for(auto [nb , wt] : adj[node]){
            if(dist[nb] > d+wt){
                dist[nb] = d+wt;
                mn[nb] = mn[node]+1;
                mx[nb] = mx[node]+1;
                ways[nb] = ways[node];
                pq.push({d+wt , nb});
            }
            else if(dist[nb] == d+wt){
                mn[nb] = min(mn[node]+1 , mn[nb]);
                mx[nb] = max(mx[node]+1 , mx[nb]);
                ways[nb] = (ways[nb]%mod + ways[node]%mod)%mod;
            }
        }
    }

    cout << dist[n] << " " << ways[n] << " " << mn[n] << " " << mx[n] << endl;
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