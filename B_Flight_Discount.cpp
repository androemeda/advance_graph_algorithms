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
vector<vector<int>> ans;

void solve() {
    cin >> n >> m;

    adj.assign(n+1 , vector<pair<int,int>>());
    ans.assign(n+1 , vector<int>(2 , LLONG_MAX));

    for(int i=0 ; i<m ; i++){
        int a , b , c;
        cin >> a >> b >> c;
        adj[a].push_back({b,c});
    }

    priority_queue<tuple<int,int,int> , vector<tuple<int,int,int>> , greater<> > pq; // dist , node , tickets-used
    pq.push({0 , 1 , 0});
    ans[1][0] = 0;

    while(!pq.empty()){

        auto [dist , node , ticks] = pq.top();
        pq.pop();

        if(dist > ans[node][ticks]) continue;

        //dont use coupon
        for(auto [nb , wt] : adj[node]){
            if(ans[nb][ticks] > dist+wt){
                ans[nb][ticks] = dist+wt;
                pq.push({dist+wt , nb , ticks});
            }
        }

        //use ticket , if available
        if(ticks == 1) continue;

        for(auto [nb , wt] : adj[node]){
            if(ans[nb][ticks+1] > dist + (wt/2) ){
                ans[nb][ticks+1] = dist + (wt/2) ;
                pq.push({dist + (wt/2) , nb , ticks+1});
            }
        }
    }

    cout << ans[n][1] << endl;

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

// if(dist > ans[node][ticks]) continue;
// priority_queue<tuple<int,int,int> , vector<tuple<int,int,int>> , greater<> > pq; // dist , node , tickets-used