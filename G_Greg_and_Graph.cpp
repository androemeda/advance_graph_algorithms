#include <iostream>
#include <vector>
#include <algorithm>
#include <limits>
#define int long long
using namespace std;

void solve() {
    int n;
    cin >> n;
    vector<vector<int>> dist(n, vector<int>(n));
    for(int i = 0; i < n; i++){
        for(int j = 0; j < n; j++){
            cin >> dist[i][j];
        }
    }
    vector<int> x(n);
    for(int i = 0; i < n; i++){
        cin >> x[i];
        --x[i];
    }
    vector<int> rev(n);
    for(int i = 0; i < n; i++){
        rev[i] = x[n - 1 - i];
    }

    vector<bool> active(n, false);
    vector<int> ans(n, 0);

    for(int k = 0; k < n; k++){
        int w = rev[k];
        active[w] = true;

        for(int i = 0; i < n; i++){
            for(int j = 0; j < n; j++){
                if(dist[i][w] + dist[w][j] < dist[i][j]){
                    dist[i][j] = dist[i][w] + dist[w][j];
                }
            }
        }

        int sum = 0;
        for(int i = 0; i < n; i++){
            if(!active[i]) continue;
            for(int j = 0; j < n; j++){
                if(active[j]) sum += dist[i][j];
            }
        }
        ans[k] = sum;
    }

    for(int i = n - 1; i >= 0; i--){
        cout << ans[i] << (i ? ' ' : '\n');
    }
}

signed main(){
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    solve();
    return 0;
}

/**
How it works

Reverse the deletions. Deleting in order x[0],x[1],… is equivalent to adding in reverse.

Incremental Floyd–Warshall. Whenever you “add” a new node w, you run

cpp
Copy
Edit
for i in 0..n-1, j in 0..n-1:
  dist[i][j] = min(dist[i][j], dist[i][w] + dist[w][j]);
so dist becomes the all-pairs shortest paths among the set of nodes you’ve added so far.

Record the sum. After each addition, sum dist[i][j] over all active i,j.

Reverse the recorded sums to report “before deletion” answers in the original order.
 */