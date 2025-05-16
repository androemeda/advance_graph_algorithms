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

int m , n;
vector<vector<char>> grid;
vector<vector<bool>> visited;

vector<vector<int>> dirs = {{0,1} , {0,-1} , {1,0} , {-1,0}};

bool dfs(int sx , int sy , int dx , int dy){
    if(sx == dx && sy == dy) return true;

    bool ans = false;

    if(sx>=0 && sx<m && sy>=0 && sy<n && grid[sx][sy] != '#' && !visited[sx][sy]){
        visited[sx][sy] = true;
        for(int i=0 ; i<4 ; i++){
            ans |= dfs(sx+dirs[i][0] , sy+dirs[i][1] , dx , dy);
        }
    }

    return ans;
}

void solve() {
    cin >> m >> n;

    grid.assign(m , vector<char>(n));
    visited.assign(m , vector<bool>(n , false));

    int sx = -1;
    int sy = -1;
    int dx = -1;
    int dy = -1;
    int openings = 0;

    for(int i=0 ; i<m ; i++){
        for(int j=0 ; j<n ; j++){
            cin >> grid[i][j];
            if(grid[i][j] == '.' && (i==0 || j==0 || i==m-1 || j==n-1)){
                if(openings == 0){
                    sx = i;
                    sy = j;
                }
                if(openings == 1){
                    dx = i;
                    dy = j;
                }
                openings++;
            }
        }
    }

    bool haspath = dfs(sx , sy , dx , dy);

    if(haspath && openings == 2) cout << "valid" << endl;
    else cout << "invalid" << endl;

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