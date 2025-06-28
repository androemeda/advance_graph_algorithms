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
vector<int> check;
vector<int> bfs;
vector<int> dist;
map<int,int> mp;

bool cmp(int a , int b){
    return mp[a] < mp[b];
}

void solve() {

    cin >> n;

    adj.assign(n+1 , vector<int>());
    dist.assign(n+1 , INT_MAX);

    for(int i=0 ; i<n-1 ; i++){
        int u , v;
        cin >> u >> v;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    for(int i=0 ; i<n ; i++){
        int x;
        cin >> x;
        check.push_back(x);
        mp[x] = i;
    }

    for(int i=0 ; i<adj.size() ; i++){
        sort(adj[i].begin() , adj[i].end() , cmp);
    }

    queue<int> q;
    q.push(1);
    dist[1] = 0;

    while(!q.empty()){
        int curr = q.front();
        bfs.push_back(curr);
        q.pop();
        for(int nb : adj[curr]){
            if(dist[nb] > 1+dist[curr]){
                dist[nb] = 1+dist[curr];
                q.push(nb);
            }
        }
    }

    if(bfs.size() != check.size()){
        cout << "No" << endl;
        return;
    }

    for(int i=0 ; i<bfs.size() ; i++){
        if(bfs[i] != check[i]){
            cout << "No" << endl;
            return;
        }
    }

    cout << "Yes" << endl;



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