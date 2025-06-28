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

vector<vector<int>> dirs = {{0,-1} , {0,1} , {1,0} , {-1,0} , {1,1} , {-1,1} , {1,-1} , {-1,-1}};

void solve() {
    int t = 1;
    while(true){
        cin >> h >> w;

        if(h == 0) break;

        grid.assign(h+1 , vector<char>(w+1));
        dp.assign(h+1 , vector<int>(w+1 , 1));

        vector<pair<char,pair<int,int>>> arr;

        for(int i=1 ; i<=h ; i++){
            for(int j=1 ; j<=w ; j++){
                cin >> grid[i][j];
                arr.push_back({grid[i][j] , {i , j}});
            }
        }

        sort(arr.begin() , arr.end());

        int ans = 0;

        for(int i=arr.size()-1 ; i>=0 ; i--){
            int cv = arr[i].first;
            int cx = arr[i].second.first;
            int cy = arr[i].second.second;

            for(int i=0 ; i<8 ; i++){
                int nx = cx+dirs[i][0];
                int ny = cy+dirs[i][1];

                if(nx>=1 && ny>=1 && nx<=h && ny<=w && grid[nx][ny]==grid[cx][cy]-1 && dp[nx][ny]<1+dp[cx][cy]){
                    dp[nx][ny] = 1+dp[cx][cy];
                }
            }
        }

        for(int i=1; i<=h ; i++){
            for(int j=1 ; j<=w ; j++){
                if(grid[i][j] == 'A') ans = max(ans , dp[i][j]);
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