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

int h , w;
vector<vector<char>> grid;
vector<vector<int>> dp;

vector<vector<int>> dirs = {{0,1} , {0,-1} , {1,0} , {-1,0} , {1,1} , {1,-1} , {-1,1} , {-1,-1}};

int dfs(int r , int c , char prev){
    int ans = 1;
    if(r >= 0 && c >= 0 && r < h && c < w){
        if(dp[r][c] != -1) return dp[r][c];
        char curr = grid[r][c];
        if(prev+1 == curr || prev == '.'){
            for(int i=0 ; i<dirs.size() ; i++){
                ans = max(ans , dfs(r+dirs[i][0] , c+dirs[i][1] , curr)+1);
            }
        }
        dp[r][c] = ans;
    }

    return ans;
}

void solve() {
    int t = 1;
    while(true){
        cin >> h >> w;
        if(h == 0 && w == 0) break;

        grid.assign(h , vector<char>(w));
        dp.assign(h , vector<int>(w , -1));

        for(int i=0 ; i<h ; i++){
            for(int j=0 ; j<w ; j++){
                cin >> grid[i][j];
            }
        }

        int ans = 0;

        for(int i=0 ; i<h ; i++){
            for(int j=0 ; j<w ; j++){
                if(grid[i][j] == 'A'){
                    ans = max(ans , dfs(i , j , '.'));
                }
            }
        }

        cout << "Case " << t << ": " << ans << endl;
        t++;
    }
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