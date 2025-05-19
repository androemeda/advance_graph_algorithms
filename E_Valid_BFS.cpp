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

int n;
vector<vector<int>> adj;
vector<set<int>> levels;
vector<int> check;
vector<bool> visited;

void solve() {

    cin >> n;

    adj.assign(n+1 , vector<int>());
    check.assign(n , 0);
    visited.assign(n+1 , false);

    for(int i=0 ; i<n-1 ; i++){
        int u , v;
        cin >> u >> v;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    for(int i=0 ; i<n ; i++){
        cin >> check[i];
    }

    queue<int> q;
    q.push(1);
    visited[1] = true;

    while(!q.empty()){
        int size = q.size();
        set<int> children;
        for(int i=0 ; i<size ; i++){
            int curr = q.front();
            children.insert(curr);
            q.pop();
            for(int nb : adj[curr]){
                if(!visited[nb]){
                    q.push(nb);
                    visited[nb] = true;
                }
            }
        }
        levels.push_back(children);
    }

    bool valid = true;

    if(check.size() != n) valid = false;

    int st = 0;

    for(int i=0 ; i<levels.size() ; i++){
        int size = levels[i].size();
        int end = st+size-1;
        for(int j=st ; j<=end ; j++){
            if(levels[i].count(check[j]) <= 0){
                valid = false;
                break;
            }
        }
        st = end+1;
    }

    if(valid) cout << "Yes" << endl;
    else cout << "No" << endl;

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


/*

CORRECT CODE


#include <iostream>
#include <vector>
#include <queue>
#include <set>
#define int long long
using namespace std;

int n;
vector<vector<int>> adj;
vector<int> check;
vector<bool> visited;

void solve() {
    cin >> n;

    adj.assign(n + 1, vector<int>());
    check.assign(n, 0);
    visited.assign(n + 1, false); // FIXED: n+1 to include node 'n'

    for (int i = 0; i < n - 1; i++) {
        int u, v;
        cin >> u >> v;
        adj[u].push_back(v);
        adj[v].push_back(u); // Undirected edge
    }

    for (int i = 0; i < n; i++) {
        cin >> check[i];
    }

    if (check[0] != 1) { // BFS must start with 1
        cout << "No" << endl;
        return;
    }

    queue<int> q;
    q.push(1);
    visited[1] = true;

    int idx = 1; // index in check[], starts from 1 because check[0] == 1

    while (!q.empty()) {
        int curr = q.front();
        q.pop();

        set<int> children;
        for (int nb : adj[curr]) {
            if (!visited[nb]) {
                children.insert(nb);
                visited[nb] = true; // Mark as visited early
            }
        }

        // Now match the next 'children.size()' nodes in check[]
        for (int i = 0; i < children.size(); ++i) {
            if (idx >= n || !children.count(check[idx])) {
                cout << "No" << endl;
                return;
            }
            q.push(check[idx]);
            idx++;
        }
    }

    cout << "Yes" << endl;
}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL); cout.tie(NULL);

    int _t = 1;
    while (_t--) {
        solve();
    }

    return 0;
}

*/