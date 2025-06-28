#include <iostream>
#include <vector>
#include <queue>
#include <string>
#include <cstring>
#include <limits>
#define int long long
using namespace std;

void solve() {
    int n, m;
    cin >> n >> m;
    vector<string> g(n);
    for(int i = 0; i < n; i++) {
        cin >> g[i];
    }

    for(int i = 0; i < n; i++) {
        for(int j = 0; j < m; j++) {
            if(g[i][j] == 'B') {
                int di[4] = {1,-1,0,0};
                int dj[4] = {0,0,1,-1};
                for(int d = 0; d < 4; d++) {
                    int ni = i + di[d], nj = j + dj[d];
                    if(ni < 0 || ni >= n || nj < 0 || nj >= m) continue;
                    if(g[ni][nj] == 'G') {
                        cout << "No\n";
                        return;
                    }
                    if(g[ni][nj] == '.') {
                        g[ni][nj] = '#';
                    }
                }
            }
        }
    }

    if(g[n-1][m-1] == '#') {
        for(int i = 0; i < n; i++) {
            for(int j = 0; j < m; j++) {
                if(g[i][j] == 'G') {
                    cout << "No\n";
                    return;
                }
            }
        }
        cout << "Yes\n";
        return;
    }

    vector<vector<bool>> vis(n, vector<bool>(m,false));
    queue<pair<int,int>> q;
    vis[n-1][m-1] = true;
    q.push({n-1, m-1});
    int di[4] = {1,-1,0,0};
    int dj[4] = {0,0,1,-1};
    while(!q.empty()) {
        auto [i,j] = q.front(); q.pop();
        for(int d = 0; d < 4; d++) {
            int ni = i + di[d], nj = j + dj[d];
            if(ni < 0 || ni >= n || nj < 0 || nj >= m) continue;
            if(vis[ni][nj]) continue;
            if(g[ni][nj] == '#') continue;
            vis[ni][nj] = true;
            q.push({ni,nj});
        }
    }
    
    for(int i = 0; i < n; i++) {
        for(int j = 0; j < m; j++) {
            if(g[i][j] == 'G' && !vis[i][j]) {
                cout << "No\n";
                return;
            }
            if(g[i][j] == 'B' && vis[i][j]) {
                cout << "No\n";
                return;
            }
        }
    }
    cout << "Yes\n";
}

signed main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL); cout.tie(NULL);

    int _t;
    cin >> _t;
    while(_t--){
        solve();
    }
    return 0;
}
