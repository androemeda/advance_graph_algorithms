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

int r , c;
vector<vector<char>> grid;
vector<vector<int>> kills;

vector<vector<int>> dirs = {{0,1} , {0,-1} , {1,0} , {-1,0}};

int bfs(int sx , int sy){
    if(sx == r && sy == c) return 0;
    
    deque<pair<int,int>> dq;
    dq.push_back({sx , sy});
    kills[sx][sy] = 0;

    while(!dq.empty()){
        auto curr = dq.front();
        int x = curr.first;
        int y = curr.second;
        dq.pop_front();

        for(int i=0 ; i<4 ; i++){
            int newx = x+dirs[i][0];
            int newy = y+dirs[i][1];
            if(newx>=0 && newy>=0 && newx<r && newy<c){
                if(grid[newx][newy] == grid[x][y] && kills[newx][newy] > kills[x][y]){
                    kills[newx][newy] = kills[x][y];
                    dq.push_front({newx , newy});
                }
                else if(grid[newx][newy] != grid[x][y] && kills[newx][newy] > 1+kills[x][y]){
                    kills[newx][newy] = 1 + kills[x][y];
                    dq.push_back({newx , newy});
                }
            }
        }
    }

    return kills[r-1][c-1];
}

void solve() {
    cin >> r >> c;

    grid.assign(r , vector<char>(c));
    kills.assign(r , vector<int>(c , INT_MAX));

    for(int i=0 ; i<r ; i++){
        string x;
        cin >> x;
        for(int j=0 ; j<c ; j++){
            grid[i][j] = x[j];
        }
    }

    int ans = bfs(0 , 0);

    cout << ans << endl;
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

/**
 * 0-1 bfs spoj problem
 */