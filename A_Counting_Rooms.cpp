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
vector<vector<bool>> visited;
vector<vector<char>> rooms;

vector<vector<int>> dirs = {{0,1} , {0,-1} , {1,0} , {-1,0}};

bool valid(int r , int c){
    return r >= 1 && c >= 1 && r <= n && c <= m && rooms[r][c] == '.';
}

void dfs(int r , int c){
    if(valid(r , c) && !visited[r][c]){
        visited[r][c] = true;
        for(int i=0 ; i<dirs.size() ; i++){
            dfs(r+dirs[i][0] , c+dirs[i][1]);
        }
    }
}

void solve() {

    cin >> n >> m;

    visited.resize(n+1 , vector<bool>(m+1 , false));
    rooms.resize(n+1 , vector<char>(m+1 , '-'));

    for(int i=1 ; i<=n ; i++){
        for(int j=1 ; j<=m ; j++){
            cin >> rooms[i][j];
        }
    }

    int ans = 0;

    for(int i=1 ; i<=n ; i++){
        for(int j=1 ; j<=m ; j++){
            if(!visited[i][j] && rooms[i][j] != '#'){
                ans++;
                dfs(i , j);
            }
        }
    }

    cout << ans << endl;
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