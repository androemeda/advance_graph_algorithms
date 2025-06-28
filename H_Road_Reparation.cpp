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
vector<vector<int>> adj;
vector<pair<int,pair<int,int>>> edges;

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

    for(int i=0 ; i<m ; i++){
        int a,b,c;
        cin >> a >> b >> c;
        edges.push_back({c , {a , b}});
    }

    sort(edges.begin() , edges.end());

    int ans = 0;
    int count = 0; //counting number of edges connected.

    DSU2 dsu(n+1);

    for(int i=0 ; i<m ; i++){
        int a = edges[i].second.first;
        int b = edges[i].second.second;
        int c = edges[i].first;
        if(dsu.findRoot(a) == dsu.findRoot(b)) continue;
        dsu.unite(a , b);
        count++;
        ans += c;
    }

    if(count == n-1) cout << ans << endl;
    else cout << "IMPOSSIBLE" << endl;

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