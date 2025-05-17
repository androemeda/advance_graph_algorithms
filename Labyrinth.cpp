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
vector<vector<char>> grid;
vector<vector<int>> dist;
vector<vector<pair<int,int>>> parent;

vector<vector<int>> dirs = {{0,1} , {0,-1} , {-1,0} , {1,0}};

char getdirection(pair<int,int> curr , pair<int,int> parent){
    if(curr.first == parent.first){
        if(curr.second < parent.second) return 'L';
        else return 'R';
    }
    else{
        if(curr.first < parent.first) return 'U';
        else return 'D';
    }
}

void bfs(int sx , int sy , int dx , int dy){
    queue<pair<int,int>> q;
    q.push({sx , sy});
    dist[sx][sy] = 0;

    while(!q.empty()){
        auto curr = q.front();
        q.pop(); 
        int x = curr.first;
        int y = curr.second;

        for(int i=0 ; i<4 ; i++){
            int newx = x+dirs[i][0];
            int newy = y+dirs[i][1];
            if(newx>=1 && newy>=1 && newx<=n && newy<=m && grid[newx][newy] != '#' && dist[newx][newy] > 1+dist[x][y]){
                dist[newx][newy] = 1 + dist[x][y];
                q.push({newx , newy});
                parent[newx][newy] = {x , y};
            }
        }
    }

    if(dist[dx][dy] == INT_MAX){
        cout << "NO";
        return;
    }
    else{
        cout << "YES" << endl;
        cout << dist[dx][dy] << endl;
        int x = dx;
        int y = dy;
        string path;
        while(!(x == sx && y == sy)){
            char dir = getdirection({x,y} , parent[x][y]);
            path.push_back(dir);
            auto p = parent[x][y];
            x = p.first;
            y = p.second;
        }
        reverse(path.begin() , path.end());
        cout << path << endl;
    }
}

void solve() {
    cin >> n >> m;

    grid.assign(n+1 , vector<char>(m+1));
    dist.assign(n+1 , vector<int>(m+1 , INT_MAX));
    parent.assign(n+1 , vector<pair<int,int>>(m+1 , {-1,-1}));

    int sx = -1;
    int sy = -1;
    int dx = -1;
    int dy = -1;

    for(int i=1 ; i<=n ; i++){
        for(int j=1 ; j<=m ; j++){
            cin >> grid[i][j];
            if(grid[i][j] == 'A'){
                sx = i;
                sy = j;
            }
            if(grid[i][j] == 'B'){
                dx = i;
                dy = j;
            }
        }
    }

    bfs(sx , sy , dx , dy);

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