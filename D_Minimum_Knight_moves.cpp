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

string s , d;
int sx , sy , dx , dy;
vector<vector<int>> steps;

vector<vector<int>> dirs = {{1,2} , {-1,2} , {1,-2} , {-1,-2} , {2,1} , {-2,1} , {2,-1} , {-2,-1}};

void solve() {

    steps.assign(8 , vector<int>(8 , INT_MAX));

    cin >> s >> d;
    sx = s[0]-'a';
    sy = s[1]-'1';
    dx = d[0]-'a';
    dy = d[1]-'1';

    queue<pair<int,int>> q;
    q.push({sx,sy});
    steps[sx][sy] = 0;

    while(!q.empty()){
        auto p = q.front();
        q.pop();
        int x = p.first;
        int y = p.second;
        if(x == dx && y == dy) break;
        for(int i=0 ; i<8 ; i++){
            int newx = x+dirs[i][0];
            int newy = y+dirs[i][1];
            if(newx>=0 && newy>=0 && newx<8 && newy<8 && steps[newx][newy] > 1+steps[x][y]){
                steps[newx][newy] = 1+steps[x][y];
                q.push({newx , newy});
            }
        }
    }

    cout << steps[dx][dy] << endl;
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