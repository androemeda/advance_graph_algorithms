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
vector<int> teams;
vector<vector<int>> adj;
bool possible = true;

vector<vector<int>> dirs = {{0,1} , {0,-1} , {1,0} , {-1,0}};

void dfs(int curr , int prevc){
    if(teams[curr] == 0){
        teams[curr] = (prevc == 1) ? 2 : 1;
        for(int i=0 ; i<adj[curr].size() ; i++){
            dfs(adj[curr][i] , teams[curr]);
        }
    }
    else if(teams[curr] == prevc){
        possible = false;
        return;
    }
}

void solve() {
    cin >> n >> m;

    adj.resize(n+1);
    teams.resize(n+1 , 0);

    for(int i=0 ; i<m ; i++){
        int a , b;
        cin >> a >> b;
        adj[a].push_back(b);
        adj[b].push_back(a);
    }

    for(int i=1 ; i<=n ; i++){
        if(teams[i] == 0){
            dfs(i , 2);
        }
    }

    if(possible){
        for(int i=1 ; i<=n ; i++){
            cout << teams[i] << " ";
        }
    }
    else{
        cout << "IMPOSSIBLE";
    }

    cout << endl;

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