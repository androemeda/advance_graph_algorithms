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

// path compression
class DSU1{
public:
    vector<int> parent;

    DSU1(int n){
        for(int i=0 ; i<n ; i++){
            parent.push_back(i);
        }
    }

    void unite(int a , int b){
        a = findRoot(a);
        b = findRoot(b);
        if(a == b) return;
        parent[b] = a;
    }

    int findRoot(int a){
        if(a == parent[a]) return a;
        return parent[a] = findRoot(parent[a]); //path compression.
    }
};

// small to large
class DSU2{
public:
    vector<int> parent;
    vector<int> size;

    DSU2(int n){
        for(int i=0 ; i<n ; i++){
            parent.push_back(i);
            size.push_back(1);
        }
    }

    void unite(int a , int b){
        a = findRoot(a);
        b = findRoot(b);

        if(a == b) return;

        if(size[a] < size[b]){
            parent[a] = b;
            size[b] += size[a];
        }
        else{
            parent[b] = a;
            size[a] += size[b];
        }
    }

    int findRoot(int a){
        if(a == parent[a]) return a;
        return findRoot(parent[a]);
    }
};

void solve() {
    cin >> n >> m;

    DSU1 dsu(n+1);

    for(int i=0 ; i<m ; i++){
        string s;
        int u , v;
        cin >> s >> u >> v;
        if(s == "union"){
            dsu.unite(u , v);
        }
        else{
            if(dsu.findRoot(u) == dsu.findRoot(v)) cout << "YES";
            else cout << "NO";
        }
        cout << endl;
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