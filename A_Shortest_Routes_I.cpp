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
vector<int> ans;

void solve() {

    cin >> n >> m;

    adj.assign(n+1 , vector<pair<int,int>>());
    ans.assign(n+1 , LLONG_MAX);

    for(int i=0 ; i<m ; i++){
        int a , b , c;
        cin >> a >> b >> c;
        adj[a].push_back({b , c});
    }

    priority_queue< pair<int,int> , vector<pair<int,int>> , greater<pair<int,int>>> pq;

    pq.push({0 , 1}); //dist , city
    ans[1] = 0;

    while(!pq.empty()){
        int dist = pq.top().first;
        int curr = pq.top().second;
        pq.pop();

        if(dist > ans[curr]) continue;

        for(pair<int,int> p : adj[curr]){
            int node = p.first;
            int wt = p.second;
            if(ans[node] > dist+wt){
                ans[node] = dist + wt;
                pq.push({ans[node] , node});
            }
        }
    }

    for(int i=1 ; i<=n ; i++){
        cout << ans[i] << " ";
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

// use LLONG_MAX AND NOT INT_MAX
//if(dist > ans[curr]) continue;