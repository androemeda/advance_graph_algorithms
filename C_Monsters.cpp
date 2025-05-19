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
vector<vector<bool>> visitedByA;
vector<vector<pair<int,int>>> parent;

vector<vector<int>> dirs = {{0,1} , {0,-1} , {-1,0} , {1,0}};

bool isValid(int newx , int newy){
    return newx>=1 && newy>=1 && newx<=n && newy<=m;
}

char getdirection(pair<int,int> c , pair<int,int> p){
    int cx = c.first;
    int cy = c.second;
    int px = p.first;
    int py = p.second;
    if(px-cx == 1) return 'U';
    else if(px-cx == -1) return 'D';
    else if(py-cy == -1) return 'R';
    else return 'L';
}

void solve() {
    cin >> n >> m;
    
    grid.assign(n+1 , vector<char>(m+1));
    dist.assign(n+1 , vector<int>(m+1 , INT_MAX));
    visitedByA.assign(n+1 , vector<bool>(m+1 , false));
    parent.assign(n+1 , vector<pair<int,int>>(m+1 , {-1,-1}));

    queue<pair<int,int>> q;

    int ax , ay;

    for(int i=1 ; i<=n ; i++){
        for(int j=1 ; j<=m ; j++){
            cin >> grid[i][j];
            if(grid[i][j] == 'M'){
                q.push({i,j});
                dist[i][j] = 0;
            }
            if(grid[i][j] == 'A'){
                ax = i;
                ay = j;
            }
        }
    }

    while(!q.empty()){
        auto curr = q.front();
        int x = curr.first;
        int y = curr.second;
        q.pop();
        for(int i=0 ; i<4 ; i++){
            int newx = x+dirs[i][0];
            int newy = y+dirs[i][1];
            if(isValid(newx , newy) && grid[newx][newy] != '#' && dist[newx][newy] > 1+dist[x][y]){
                dist[newx][newy] = 1+dist[x][y];
                q.push({newx , newy});
            }
        }
    }

    // for(int i=1 ; i<=n ; i++){
    //     for(int j=1 ; j<=m ; j++){
    //         (dist[i][j] == INT_MAX) ? cout << "_" : cout << dist[i][j];
    //         cout << "\t";
    //     }
    //     cout << endl;
    // }

    // return;

    q = queue<pair<int,int>>();
    q.push({ax , ay});
    visitedByA[ax][ay] = true;
    dist[ax][ay] = 0;

    int steps = 0;
    bool possible = false;

    int ansx , ansy;

    while(!q.empty()){
        auto curr = q.front();
        int x = curr.first;
        int y = curr.second;
        q.pop();
        if(isValid(x , y) && (x==1 || y==1 || x==n || y==m)){
            possible = true;
            steps = dist[x][y];
            ansx = x;
            ansy = y;
            break;
        }
        for(int i=0 ; i<4 ; i++){
            int newx = x+dirs[i][0];
            int newy = y+dirs[i][1];
            if(isValid(newx , newy) && !visitedByA[newx][newy] && grid[newx][newy] != '#' && dist[newx][newy] > 1+dist[x][y]){
                q.push({newx , newy});
                dist[newx][newy] = 1+dist[x][y];
                visitedByA[newx][newy] = true;
                parent[newx][newy] = {x , y};
            }
        }
    }

    // while(ansx != -1){
    //     cout << ansx << " " << ansy << endl;
    //     auto p = parent[ansx][ansy];
    //     ansx = p.first;
    //     ansy = p.second;
    // }

    // for(int i=1 ; i<=n ; i++){
    //     for(int j=1 ; j<=m ; j++){
    //         (dist[i][j] == INT_MAX) ? cout << "_" : cout << dist[i][j];
    //         cout << "\t";
    //     }
    //     cout << endl;
    // }

    // return;

    if(possible){
        cout << "YES" << endl << steps << endl;
        
        string path;

        while(parent[ansx][ansy].first != -1){
            auto p = parent[ansx][ansy];
            // cout << ansx << "," << ansy << "-->" << p.first << "," << p.second << " : ";
            
            path.push_back(getdirection({ansx , ansy} , p));

            ansx = p.first;
            ansy = p.second;
        }

        reverse(path.begin() , path.end());

        cout << path << endl;
    }
    else{
        cout << "NO" << endl;
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