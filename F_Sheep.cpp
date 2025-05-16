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
vector<vector<char>> grid;
vector<vector<bool>> visited;

vector<vector<int>> dirs = {{0,1} , {0,-1} , {1,0} , {-1,0}};

tuple<int , int , bool> dfs(int r , int c){
    int sheep = 0;
    int wolves = 0;
    bool canflee = false;

    if(r >= 0 && c >= 0 && r < n && c < m && grid[r][c] != '#' && !visited[r][c]){
        if(grid[r][c] == 'k') sheep++;
        if(grid[r][c] == 'v') wolves++;
        if(r == 0 || c == 0 || r == n-1 || c == m-1) canflee = true;
        visited[r][c] = true;
        for(int i=0 ; i<4 ; i++){
            auto [s , w , cf] = dfs(r+dirs[i][0] , c+dirs[i][1]);
            sheep += s;
            wolves += w;
            canflee |= cf;
        }
    }

    return {sheep , wolves , canflee};
}

void solve() {
    cin >> n >> m;

    grid.assign(n , vector<char>(m));
    visited.assign(n , vector<bool>(m , false));

    for(int i=0 ; i<n ; i++){
        for(int j=0 ; j<m ; j++){
            cin >> grid[i][j];
        }
    }

    int sheep = 0;
    int wolves = 0;

    for(int i=0 ; i<n ; i++){
        for(int j=0 ; j<m ; j++){
            if(visited[i][j]) continue;
            auto [s ,  w , canflee] = dfs(i , j);
            if(canflee){
                sheep += s;
                wolves += w;
            }
            else if(s > w) sheep += s;
            else wolves += w;
        }
    }

    cout << sheep << " " << wolves << endl;
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