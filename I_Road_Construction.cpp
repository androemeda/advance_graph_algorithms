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

// small to large
class DSU2{
public:
    vector<int> parent;
    vector<int> size;
    int comps;
    int mxsz;

    DSU2(int n){
        for(int i=0 ; i<n ; i++){
            parent.push_back(i);
            size.push_back(1);
        }
        comps = n;
        mxsz = 1;
    }

    void unite(int a , int b){
        a = findRoot(a);
        b = findRoot(b);
        if(a == b) return;
        if(size[a] < size[b]){
            parent[a] = b;
            size[b] += size[a];
            mxsz = max(size[b] , mxsz);
        }
        else{
            parent[b] = a;
            size[a] += size[b];
            mxsz = max(size[a] , mxsz);
        }
        comps--;
    }

    int findRoot(int a){
        if(a == parent[a]) return a;
        return findRoot(parent[a]);
    }
};

void solve() {
    cin >> n >> m;

    DSU2 dsu(n+1);

    for(int i=0 ; i<m ; i++){
        int a,b;
        cin >> a >> b;
        dsu.unite(a , b);
        cout << dsu.comps-1 << " " << dsu.mxsz << endl;
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