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

int n , m , q;
vector<vector<int>> dist;

void solve() {
    cin >> n >> m >> q;

    dist.assign(n+1 , vector<int>(n+1 , LLONG_MAX));
    for(int i=1 ; i<=n  ;i++) dist[i][i] = 0;

    for(int i=0  ;i<m ; i++){
        int a , b , c;
        cin >> a >> b >> c;
        dist[a][b] = min(dist[a][b] , c);
        dist[b][a] = min(dist[b][a] , c);
    }

    //implement floys-warshall
    for(int k=1 ; k<=n ; k++){
        for(int i=1 ; i<=n ; i++){
            for(int j=1 ; j<=n ; j++){
                if (dist[i][k] != LLONG_MAX && dist[k][j] != LLONG_MAX) {
                    dist[i][j] = min(dist[i][j], dist[i][k] + dist[k][j]);
                }
            }
        }
    }

    for(int i=0  ;i<q ; i++){
        int s , d;
        cin >> s >> d;
        if(dist[s][d] == LLONG_MAX) cout << -1 << endl;
        else cout << dist[s][d] << endl;
    }
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

/*
floyd-warshall algorithm -> use to find shortest dist b/w all pair of nodes in n^3 time complexity

for(int i=1 ; i<=n  ;i++) dist[i][i] = 0; --> initialize diagonal with zero

llong_max and overflow check

dist[i][j] = min(dist[i][j], dist[i][k] + dist[k][j]);
*/