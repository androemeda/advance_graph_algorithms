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
    cin >> n;
    int people = 0;
    map<string , int> mp;
    DSU2 dsu(100010);
    for(int i=0 ; i<n ; i++){
        string p1 , p2;
        cin >> p1 >> p2;
        if(mp.count(p1) == 0){
            people++;
            mp[p1] = people;
        }
        if(mp.count(p2) == 0){
            people++;
            mp[p2] = people;
        }
        dsu.unite(mp[p1] , mp[p2]);
        cout << dsu.size[dsu.findRoot(mp[p1])] << endl;
    }
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