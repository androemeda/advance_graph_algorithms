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

const int MAX = 5e5 + 10;

class DSU2{
public:
    vector<int> parent;
    vector<int> size;

    DSU2(int n){
        parent.resize(n);
        size.resize(n, 1);
        for(int i = 0; i < n; i++){
            parent[i] = i;
        }
    }

    void unite(int a, int b){
        a = findRoot(a);
        b = findRoot(b);

        if(a == b) return;

        if(size[a] < size[b]){
            parent[a] = b;
            size[b] += size[a];
        } else {
            parent[b] = a;
            size[a] += size[b];
        }
    }

    int findRoot(int a){
        if(a == parent[a]) return a;
        return parent[a] = findRoot(parent[a]); // Path compression
    }
};

void solve() {
    int q;
    cin >> q;

    DSU2 dsu(MAX);
    vector<int> result;

    for(int i = 0; i < q; i++){
        int type;
        cin >> type;

        if(type == 1){
            int x;
            cin >> x;
            result.push_back(x);
        }
        else if(type == 2){
            int x, y;
            cin >> x >> y;

            int root_x = dsu.findRoot(x);
            int root_y = dsu.findRoot(y);
            if(root_x != root_y){
                dsu.unite(x, y);
            }
        }
    }

    for(int &val : result){
        val = dsu.findRoot(val);
    }

    for(int x : result){
        cout << x << " ";
    }
    cout << '\n';
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